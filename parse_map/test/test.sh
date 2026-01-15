#!/bin/bash

TEST1=test_judge_data
TEST2=test_map_builder
TEST3=test_process_color
TEST4=test_process_texture
# TEST5=test_read_data

cc -Wall -Wextra -Werror -I../includes test_judge_data.c ../judge_data.c -o TEST1
cc -Wall -Wextra -Werror -I../includes test_map_builder.c ../map_builder.c -o TEST2
cc -Wall -Wextra -Werror -I../includes test_process_color.c ../process_texture_color.c ../map_info_fn.c -o TEST3
cc -Wall -Wextra -Werror -I../includes test_process_texture.c ../process_texture_color.c ../map_info_fn.c -o TEST4
# cc -Wall -Wextra -Werror -I../includes test_read_data.c ../read_data.c ../get_next_line.c -o TEST5

cc -Wall -Wextra -Werror -I../includes test_normalize_rectangle.c ../map_normalize_rectangle.c -o TEST6
cc -Wall -Wextra -Werror -I../includes test_scan_set_start.c ../map_scan_set_start.c -o TEST7
cc -Wall -Wextra -Werror test_validate_closed.c ../map_validate_closed.c -o TEST8

./TEST1
./TEST2
./TEST3
./TEST4
# ./TEST5
./TEST6
./TEST7
./TEST8

rm -f TEST1
rm -f TEST2
rm -f TEST3
rm -f TEST4
# rm -f TEST5
rm -f TEST6
rm -f TEST7
rm -f TEST8
