#!/bin/bash

generate_data() {
    case $1 in
        small)
            shuf -i 1-1000 -n 1000000
            ;;
        large)
            shuf -i 1-1000000 -n 1000000
            ;;
        signed)
            awk 'BEGIN { srand(); for (i=0; i<1000000; i++) print int(rand() * 2001) - 1000 }'
            ;;
        *) echo "Invalid dataset"; exit 1 ;;
    esac
}

test_sort() {
    local mode=$1
    local data=$2
    local input="data_${data}.txt"
    local output="out_${mode}_${data}.txt"
    local localtime="time_${mode}_${data}.txt"

    generate_data "$data" > "$input"
    echo "Testing $mode sort with $data data..."
    command time -f "%e seconds" -o "$localtime" ./sort "$mode" < "$input" > "$output"
    if ! awk '{for(i=2;i<=NF;i++) if($i<$(i-1)) exit 1}' "$output"; then
        echo "Sort failed!"
        exit 1
    fi
    echo "Time: $(cat $localtime)"
}

test_sort counting small
test_sort radix small
test_sort counting large
test_sort radix large
test_sort counting signed
test_sort radix signed

