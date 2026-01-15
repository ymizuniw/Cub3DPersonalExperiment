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
    -o "$DIR/test_parse_data"

echo ""
echo "=== Test 1: valid_simple.cub ==="
"$DIR/test_parse_data" "$DIR/data/valid_simple.cub"

echo ""
echo "=== Test 2: valid_with_empty_lines.cub ==="
"$DIR/test_parse_data" "$DIR/data/valid_with_empty_lines.cub"

echo ""
echo "=== Test 3: valid_with_spaces.cub ==="
"$DIR/test_parse_data" "$DIR/data/valid_with_spaces.cub"

echo ""
echo "=== Test 4: missing_ceiling.cub (should fail) ==="
"$DIR/test_parse_data" "$DIR/data/missing_ceiling.cub" || echo "Expected failure: missing ceiling"

echo ""
echo "=== Test 5: invalid_element.cub (should fail) ==="
"$DIR/test_parse_data" "$DIR/data/invalid_element.cub" || echo "Expected failure: invalid element"

echo ""
echo "=== Test 6: invalid_map_char.cub (should fail) ==="
"$DIR/test_parse_data" "$DIR/data/invalid_map_char.cub" || echo "Expected failure: invalid map char"

rm -f "$DIR/test_parse_data"
echo ""
echo "=== All tests completed ==="
