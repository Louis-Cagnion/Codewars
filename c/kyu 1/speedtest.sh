#!/bin/bash
clues="${1:-7 0 0 0 2 2 3 0 0 3 0 0 0 0 3 0 3 0 0 5 0 0 0 0 0 5 0 4}"
N="${2:-20}"
total=0

for i in $(seq 1 $N); do
    t=$( (/usr/bin/time -p ./Skyscraper "$clues") 2>&1 | grep real | awk '{print $2}' )
    echo "Run $i: $t s"
    total=$(echo "$total + $t" | bc)
done

average=$(echo "scale=2; $total / $N" | bc)
echo "Average time over $N runs: $average s"
