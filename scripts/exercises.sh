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
    find "$matches" -maxdepth 1 -name '*.c' | sort
}
# Every exercises/<topic>/<task>.c is checked by tests/<topic>/<task>.c.
use_file() {
    source=$1
    relative=${source#exercises/}
    tests=tests/$relative
}
select_file() {
    [ "$#" -eq 2 ] || fail "Usage: make $command <lesson> <task>"
    task=$(number "$2")
    files=$(lesson_files "$1" | sed -n "/\/${task}_[^/]*\.c$/p")
    [ "$(printf '%s\n' "$files" | sed '/^$/d' | wc -l)" -eq 1 ] || fail "Task $2 not found or ambiguous in lesson $1"
    use_file "$files"
}
compile() {
    mkdir -p "$(dirname "$binary")"
    # CC and CFLAGS deliberately support whitespace-separated compiler options.
    ${CC:-gcc} ${CFLAGS:--Wall -Wextra -Werror -Wpedantic -O2} "$1" -o "$binary"
}
test_status() {
    binary=.build/${relative%.c}_test
    log=.build/${relative%.c}.log
    mkdir -p "$(dirname "$binary")"
    if [ ! -f "$tests" ]; then
        status=SKIP
    elif (compile "$tests" && sh -c '"$1"; result=$?; exit "$result"' sh "$binary") >"$log" 2>&1; then
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
    cp -p "$source" "$backup_dir/$relative"
    printf 'Backup: %s\n' "$backup_dir/$relative"
}
case "$command" in
help)
    printf '%s\n' 'make run|test|format|reset <lesson> <task>' 'make check [lesson]' 'make stats' 'CLI arguments: make run 0 6 RUN_ARGS="10 -3 7 5"'
    ;;
run|test|format|reset)
    select_file "$@"
    binary=.build/${relative%.c}_$command
    case "$command" in
    run) compile "$source"; "$binary" ${RUN_ARGS:-};;
    test) [ -f "$tests" ] || fail "No tests: $tests"; compile "$tests"; "$binary";;
    format) clang-format -i "$source";;
    reset)
        # The clean task lives in the branch without solutions.
        base=${BASE:-master}
        git cat-file -e "$base:$source" 2>/dev/null || fail "No $source in branch $base"
        backup
        git show "$base:$source" >"$source"
        printf 'Reset: %s (from %s)\n' "$source" "$base";;
    esac
    ;;
check)
    [ "$#" -le 1 ] || fail 'Usage: make check [lesson]'
    if [ "$#" -eq 1 ]; then files=$(lesson_files "$1"); else files=$(find exercises -name '*.c' | sort); fi
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
        for file in $(find "$directory" -maxdepth 1 -name '*.c' | sort); do
            use_file "$file"
            test_status
            topic_total=$((topic_total + 1))
            case "$status" in
            PASS) topic_passed=$((topic_passed + 1));;
            FAIL) [ -n "$next" ] || next=$relative;;
            esac
            printf '  %-28s %s\n' "$(basename "$file" .c)" "$status"
        done
        progress "$topic" "$topic_passed" "$topic_total"
        all_passed=$((all_passed + topic_passed)); all_total=$((all_total + topic_total))
    done
    printf '\n'
    progress 'Total' "$all_passed" "$all_total"
    if [ -n "$next" ]; then
        printf 'Next exercise: exercises/%s\n' "$next"
        lesson_number=${next%%_*}; task_number=${next##*/}; task_number=${task_number%%_*}
        printf 'Run: make test %s %s\n' "$lesson_number" "$task_number"
    fi
    ;;
*) fail "Unknown command: $command";;
esac
