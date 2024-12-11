#!/usr/bin/env bash

input="${1:-input}"

for file in */*.c; do
    dir=${file%%/*}
    gcc -Wall -Wextra -pedantic "${file}" -o test -lm
    printf "Testing %s with %s/%s. Result: " "${file}" "${dir}" "${input}"
    ./test "${dir}/${input}"
done

rm -f test
