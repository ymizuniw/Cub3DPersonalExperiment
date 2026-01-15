#!/bin/bash

set -e

DIR=$(cd -- "$(dirname "$0")" && pwd)
SRC="$DIR/.."

echo "=== Building test_type_judgment ==="
cc -Wall -Wextra -Werror -I"$SRC/includes" \
    "$DIR/test_type_judgment.c" \
    "$SRC/read_data.c" \
    "$SRC/get_next_line.c" \
    "$SRC/judge_data.c" \
    -o "$DIR/test_type_judgment"

echo ""
echo "========================================"
echo "Test 1: valid_simple.cub"
echo "========================================"
"$DIR/test_type_judgment" "$DIR/data/valid_simple.cub"

echo ""
echo "========================================"
echo "Test 2: valid_with_empty_lines.cub"
echo "========================================"
"$DIR/test_type_judgment" "$DIR/data/valid_with_empty_lines.cub"

echo ""
echo "========================================"
echo "Test 3: valid_with_spaces.cub"
echo "========================================"
"$DIR/test_type_judgment" "$DIR/data/valid_with_spaces.cub"

echo ""
echo "========================================"
echo "Test 4: missing_ceiling.cub"
echo "========================================"
"$DIR/test_type_judgment" "$DIR/data/missing_ceiling.cub"

echo ""
echo "========================================"
echo "Test 5: invalid_element.cub"
echo "========================================"
"$DIR/test_type_judgment" "$DIR/data/invalid_element.cub"

echo ""
echo "========================================"
echo "Test 6: invalid_map_char.cub"
echo "========================================"
"$DIR/test_type_judgment" "$DIR/data/invalid_map_char.cub"

rm -f "$DIR/test_type_judgment"
echo ""
echo "=== All type judgment tests completed ==="
