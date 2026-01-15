#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"/..

CC=${CC:-cc}
CFLAGS="-Wall -Wextra -Werror -g"
INCLUDES="-Iincludes"
SRCS=(
  parse_data.c
  judge_data.c
  process_texture_color.c
  read_data.c
  get_next_line.c
  map_builder.c
  map_normalize_rectangle.c
  map_scan_set_start.c
  map_validate_closed.c
  map_info_fn.c
  flag_status_ok.c
  ft_putstr_fd.c
  test/test_parse_data.c
)

BIN="leak_check_parse_data"
echo "[build] $BIN (no ASan; using macOS leaks)"
$CC $CFLAGS $INCLUDES "${SRCS[@]}" -o "$BIN"

FAILS_DIR="test/leaks"
ok=0	nok=0
for f in "$FAILS_DIR"/fail_*.cub; do
  echo "[run] $f (expect fail, and no leaks)"
  if ./$BIN "$f" >/dev/null 2>&1; then
    echo "[KO] expected failure but succeeded: $f"
    ((nok++)) || true
  else
    echo "[OK] failed as expected: $f"
  fi
  if leaks --atExit -- ./$BIN "$f" >/dev/null 2>&1; then
    echo "[OK] no leaks: $f"
    ((ok++)) || true
  else
    echo "[KO] leaks detected: $f"
    ((nok++)) || true
  fi
done

echo "[run] valid_ok.cub (expect success and no leaks)"
if ./$BIN "$FAILS_DIR/valid_ok.cub" >/dev/null; then
  if leaks --atExit -- ./$BIN "$FAILS_DIR/valid_ok.cub" >/dev/null 2>&1; then
    echo "[OK] success and no leaks: valid_ok.cub"
  else
    echo "[KO] leaks detected on success path: valid_ok.cub"
    ((nok++)) || true
  fi
else
  echo "[KO] expected success but failed: valid_ok.cub"
  ((nok++)) || true
fi

echo "Summary: OK=$ok NG=$nok"
exit $(( nok == 0 ? 0 : 1 ))