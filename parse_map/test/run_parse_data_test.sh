#!/bin/bash

set -e

DIR=$(cd -- "$(dirname "$0")" && pwd)
SRC="$DIR/.."

echo "=== Building test_parse_data ==="
cc -Wall -Wextra -Werror -I"$SRC/includes" \
    "$DIR/test_parse_data.c" \
    "$SRC/parse_data.c" \
    "$SRC/read_data.c" \
    "$SRC/get_next_line.c" \
    "$SRC/judge_data.c" \
    "$SRC/map_info_fn.c" \
    "$SRC/flag_status_ok.c" \
    "$SRC/map_builder.c" \
    "$SRC/map_normalize_rectangle.c" \
    "$SRC/map_scan_set_start.c" \
    "$SRC/map_validate_closed.c" \
    "$SRC/process_texture_color.c" \
    "$SRC/ft_putstr_fd.c" \
    -o "$DIR/test_parse_data"

echo ""

# Run tests with automatic pass/fail detection
TOTAL=0
PASSED=0

for cubfile in "$DIR/data"/*.cub; do
    basename=$(basename "$cubfile" .cub)
    expectfile="$DIR/data/$basename.expect"
    
    if [ ! -f "$expectfile" ]; then
        echo "=== WARNING: No .expect file for $basename.cub, skipping ==="
        continue
    fi
    
    TOTAL=$((TOTAL + 1))
    expect_exit=$(cat "$expectfile")
    
    echo "=== Test $TOTAL: $basename.cub (expect exit=$expect_exit) ==="
    
    if "$DIR/test_parse_data" "$cubfile"; then
        actual_exit=0
    else
        actual_exit=1
    fi
    
    if [ "$actual_exit" -eq "$expect_exit" ]; then
        echo "✓ PASS: exit code matched ($actual_exit)"
        PASSED=$((PASSED + 1))
    else
        echo "✗ FAIL: expected exit=$expect_exit, got exit=$actual_exit"
    fi
    echo ""
done

rm -f "$DIR/test_parse_data"

echo "=== Summary: $PASSED/$TOTAL tests passed ==="
if [ "$PASSED" -eq "$TOTAL" ]; then
    exit 0
else
    exit 1
fi
