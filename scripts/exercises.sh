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
    matches=$(find templates -mindepth 1 -maxdepth 1 -type d -name "${lesson}_*" | sort)
    [ "$(printf '%s\n' "$matches" | sed '/^$/d' | wc -l)" -eq 1 ] || fail "Lesson $1 not found or ambiguous"
    find "$matches" -maxdepth 1 -name '*.c' | sort
}
select_file() {
    [ "$#" -eq 2 ] || fail "Usage: make $command <lesson> <task>"
    task=$(number "$2")
    files=$(lesson_files "$1" | sed -n "/\/${task}_[^/]*\.c$/p")
    [ "$(printf '%s\n' "$files" | sed '/^$/d' | wc -l)" -eq 1 ] || fail "Task $2 not found or ambiguous in lesson $1"
    relative=${files#templates/}
    source=exercises/$relative
}
compile() {
    mkdir -p .build
    # CC and CFLAGS deliberately support whitespace-separated compiler options.
    ${CC:-gcc} ${CFLAGS:--Wall -Wextra -Werror -Wpedantic -O2} "$@" "$source" -o "$binary"
}
has_tests() { grep -Eq '^#(ifndef|ifdef) TEST|^#if.*defined\(TEST\)' "$source"; }
test_status() {
    binary=.build/${relative%.c}_test
    log=.build/${relative%.c}.log
    mkdir -p "$(dirname "$binary")"
    if [ ! -f "$source" ]; then
        status=MISSING
    elif ! has_tests; then
        status=SKIP
    elif (compile -DTEST && sh -c '"$1"; result=$?; exit "$result"' sh "$binary") >"$log" 2>&1; then
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
    if [ -f "$source" ]; then
        mkdir -p .backups
        backup_dir=$(mktemp -d .backups/"$(date +%Y-%m-%d_%H%M%S)".XXXXXX)
        mkdir -p "$backup_dir/$(dirname "$relative")"
        cp -p "$source" "$backup_dir/$relative"
        printf 'Backup: %s\n' "$backup_dir/$relative"
    fi
}
restore() {
    backup
    mkdir -p "$(dirname "$source")"
    cp -p "templates/$relative" "$source"
    printf 'Reset: %s\n' "$source"
}
case "$command" in
help)
    printf '%s\n' 'make run|test|format|reset|save <lesson> <task>' 'make check [lesson]' 'make stats' 'make reset-all' 'CLI arguments: make run 0 6 RUN_ARGS="10 -3 7 5"'
    ;;
run|test|format|reset|save)
    select_file "$@"
    binary=.build/$(basename "$source" .c)_$command
    case "$command" in
    run) compile; "$binary" ${RUN_ARGS:-};;
    test) has_tests || fail "No built-in tests: $source"; compile -DTEST; "$binary";;
    format) clang-format -i "$source";;
    reset) restore;;
    save)
        [ -f "$source" ] || fail "Working file not found: $source"
        backup
        mkdir -p "solutions/$(dirname "$relative")"
        if [ -f "solutions/$relative" ]; then
            mkdir -p .backups
            saved_backup=$(mktemp -d .backups/"$(date +%Y-%m-%d_%H%M%S)".XXXXXX)
            mkdir -p "$saved_backup/solutions/$(dirname "$relative")"
            cp -p "solutions/$relative" "$saved_backup/solutions/$relative"
            printf 'Backup: %s\n' "$saved_backup/solutions/$relative"
        fi
        cp -p "$source" "solutions/$relative"
        printf 'Saved: solutions/%s\n' "$relative";;
    esac
    ;;
reset-all)
    [ "$#" -eq 0 ] || fail 'Usage: make reset-all'
    for file in $(find templates -name '*.c' | sort); do
        relative=${file#templates/}; source=exercises/$relative; restore
    done
    ;;
check)
    [ "$#" -le 1 ] || fail 'Usage: make check [lesson]'
    if [ "$#" -eq 1 ]; then files=$(lesson_files "$1"); else files=$(find templates -name '*.c' | sort); fi
    passed=0; total=0; skipped=0
    mkdir -p .build
    for file in $files; do
        relative=${file#templates/}; source=exercises/$relative
        test_status
        if [ "$status" = SKIP ]; then
            printf '%-36s SKIP (no tests)\n' "$relative"; skipped=$((skipped+1)); continue
        fi
        total=$((total+1))
        if [ "$status" = PASS ]; then
            printf '%-36s PASS\n' "$relative"; passed=$((passed+1))
        elif [ "$status" = MISSING ]; then
            printf '%-36s FAIL (missing file)\n' "$relative"
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
    for directory in $(find templates -mindepth 1 -maxdepth 1 -type d | sort); do
        topic=${directory#templates/}; topic_passed=0; topic_total=0
        printf '\n%s\n' "$topic"
        for file in $(find "$directory" -maxdepth 1 -name '*.c' | sort); do
            relative=${file#templates/}; source=exercises/$relative
            # Saved solutions carry progress after resetting working files.
            if [ -f "solutions/$relative" ]; then source=solutions/$relative; fi
            test_status
            topic_total=$((topic_total + 1))
            case "$status" in
            PASS) topic_passed=$((topic_passed + 1));;
            FAIL) [ -n "$next" ] || next=$relative;;
            MISSING) [ -n "$next" ] || next=$relative;;
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
