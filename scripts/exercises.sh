#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
ulimit -c 0 2>/dev/null || :
command=${1:-help}
shift || :
fail() { printf '%s\n' "$*" >&2; exit 1; }
number() {
    case "$1" in ''|*[!0-9]*) fail "Expected a numeric lesson/task: $1";; esac
    value=$(printf '%s' "$1" | sed 's/^0*//')
    printf '%02d' "${value:-0}"
}
lesson_files() {
    lesson=$(number "$1")
    matches=$(find exercises -mindepth 1 -maxdepth 1 -type d -name "${lesson}_*" | sort)
    [ "$(printf '%s\n' "$matches" | sed '/^$/d' | wc -l)" -eq 1 ] || fail "Lesson $1 not found or ambiguous"
    tasks_in "$matches"
}
# A task is a .c file or, for multi-file tasks, a directory with main.c.
tasks_in() { find "$1" -mindepth 1 -maxdepth 1 \( -name '*.c' -o -type d \) | sort; }
all_files() {
    for directory in $(find exercises -mindepth 1 -maxdepth 1 -type d | sort); do tasks_in "$directory"; done
}
# exercises/<topic>/<task> is checked by tests/<topic>/<task>.c.
use_file() {
    source=$1
    relative=${source#exercises/}
    relative=${relative%.c}
    tests=tests/$relative.c
}
select_file() {
    [ "$#" -eq 2 ] || fail "Usage: make $command <lesson> <task>"
    task=$(number "$2")
    files=$(lesson_files "$1" | sed -n "/\/${task}_[^/]*$/p")
    [ "$(printf '%s\n' "$files" | sed '/^$/d' | wc -l)" -eq 1 ] || fail "Task $2 not found or ambiguous in lesson $1"
    use_file "$files"
}
compile() {
    mkdir -p "$(dirname "$binary")"
    # CC and CFLAGS deliberately support whitespace-separated compiler options.
    ${CC:-gcc} ${CFLAGS:--Wall -Wextra -Werror -Wpedantic -O2} "$@" -o "$binary"
}
# A directory task is built by its own Makefile, without our compiler flags.
build_module() {
    [ -f "$source/Makefile" ] || fail "No Makefile in $source yet"
    (unset CC CFLAGS MAKEFLAGS MFLAGS MAKELEVEL; make -s -C "$source" clean && make -s -C "$source") \
        || fail "make failed in $source"
    [ -x "$source/app" ] || fail "$source/Makefile must build ./app"
}
build_tests() {
    if [ -d "$source" ]; then
        build_module
        compile -I"$source" "$tests" $(find "$source" -maxdepth 1 -name '*.c' ! -name main.c | sort)
    else
        compile "$tests"
    fi
}
test_status() {
    binary=.build/${relative}_test
    log=.build/$relative.log
    mkdir -p "$(dirname "$binary")"
    if [ ! -f "$tests" ]; then
        status=SKIP
    # handle_abort keeps a failed assert from producing a slow core dump.
    elif (build_tests && ASAN_OPTIONS=handle_abort=1 sh -c '"$1"; result=$?; exit "$result"' sh "$binary") >"$log" 2>&1; then
        status=PASS
    else
        status=FAIL
    fi
}
progress() {
    label=$1; done_count=$2; task_count=$3
    percent=0
    if [ "$task_count" -gt 0 ]; then percent=$((done_count * 100 / task_count)); fi
    filled=$((percent / 5)); bar=''; index=0
    while [ "$index" -lt 20 ]; do
        if [ "$index" -lt "$filled" ]; then bar="${bar}#"; else bar="${bar}-"; fi
        index=$((index + 1))
    done
    printf '%s [%s] %d/%d (%d%%)\n' "$label" "$bar" "$done_count" "$task_count" "$percent"
}
backup() {
    mkdir -p .backups
    backup_dir=$(mktemp -d .backups/"$(date +%Y-%m-%d_%H%M%S)".XXXXXX)
    mkdir -p "$backup_dir/$(dirname "$relative")"
    cp -pR "$source" "$backup_dir/$(dirname "$relative")/"
    printf 'Backup: %s\n' "$backup_dir/${source#exercises/}"
}
case "$command" in
help)
    printf '%s\n' 'make run|test|format|reset <lesson> <task>' 'make check [lesson]' 'make stats' 'CLI arguments: make run 0 6 RUN_ARGS="10 -3 7 5"'
    ;;
run|test|format|reset)
    select_file "$@"
    binary=.build/${relative}_$command
    case "$command" in
    run)
        if [ -d "$source" ]; then build_module; binary=$source/app; else compile "$source"; fi
        "$binary" ${RUN_ARGS:-};;
    test) [ -f "$tests" ] || fail "No tests: $tests"; build_tests; "$binary";;
    format)
        if [ -d "$source" ]; then
            find "$source" -maxdepth 1 \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +
        else
            clang-format -i "$source"
        fi;;
    reset)
        # The clean task lives in the branch without solutions.
        base=${BASE:-master}
        git cat-file -e "$base:$source" 2>/dev/null || fail "No $source in branch $base"
        backup
        rm -rf "$source"
        git restore --source="$base" --worktree -- "$source"
        printf 'Reset: %s (from %s)\n' "$source" "$base";;
    esac
    ;;
check)
    [ "$#" -le 1 ] || fail 'Usage: make check [lesson]'
    if [ "$#" -eq 1 ]; then files=$(lesson_files "$1"); else files=$(all_files); fi
    passed=0; total=0; skipped=0
    for file in $files; do
        use_file "$file"
        test_status
        if [ "$status" = SKIP ]; then
            printf '%-36s SKIP (no tests)\n' "$relative"; skipped=$((skipped+1)); continue
        fi
        total=$((total+1))
        if [ "$status" = PASS ]; then
            printf '%-36s PASS\n' "$relative"; passed=$((passed+1))
        else
            printf '%-36s FAIL (%s)\n' "$relative" "$log"
        fi
    done
    printf '\n%d/%d passed; %d skipped\n' "$passed" "$total" "$skipped"
    [ "$passed" -eq "$total" ]
    ;;
stats)
    [ "$#" -eq 0 ] || fail 'Usage: make stats'
    all_passed=0; all_total=0; next=''
    for directory in $(find exercises -mindepth 1 -maxdepth 1 -type d | sort); do
        topic=${directory#exercises/}; topic_passed=0; topic_total=0
        printf '\n%s\n' "$topic"
        for file in $(tasks_in "$directory"); do
            use_file "$file"
            test_status
            topic_total=$((topic_total + 1))
            case "$status" in
            PASS) topic_passed=$((topic_passed + 1));;
            FAIL) [ -n "$next" ] || { next=$relative; next_source=$source; };;
            esac
            printf '  %-28s %s\n' "${relative##*/}" "$status"
        done
        progress "$topic" "$topic_passed" "$topic_total"
        all_passed=$((all_passed + topic_passed)); all_total=$((all_total + topic_total))
    done
    printf '\n'
    progress 'Total' "$all_passed" "$all_total"
    if [ -n "$next" ]; then
        printf 'Next exercise: %s\n' "$next_source"
        lesson_number=${next%%_*}; task_number=${next##*/}; task_number=${task_number%%_*}
        printf 'Run: make test %s %s\n' "$lesson_number" "$task_number"
    fi
    ;;
*) fail "Unknown command: $command";;
esac
