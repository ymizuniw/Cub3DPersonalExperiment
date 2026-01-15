#include "includes/judge_data.h"
#include "includes/map_builder.h"
#include "includes/map_info.h"
#include "includes/map_normalize_rectangle.h"
#include "includes/parser.h"
#include "includes/read_data.h"
#include <stdio.h>
#include <stdlib.h>

//read_data()
//judge_data()
//process_data()
//process_map()

// typedef enum e_judge_type
// {
// 	J_EMPTY,    // 空行 ""
// 	J_ELEM_NO,  // NO ./path
// 	J_ELEM_SO,  // SO ./path
// 	J_ELEM_WE,  // WE ./path
// 	J_ELEM_EA,  // EA ./path
// 	J_ELEM_F,   // F r,g,b
// 	J_ELEM_C,   // C r,g,b
// 	J_MAP_LINE, // マップ行
// 	J_INVALID   // 不正
// }				t_judge_type;

// 1. read each line and judge type correctly.->OK!
// 2. renew flags corresponding to judged type.
// 3. parse each line and detect error or set value.
// 4. parse map content when other elements are fully set.

void free_map(char **map)
{
    size_t i = 0;

    while(map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

int except_map_flags_ok(bool *flag_status)
{
    if (flag_status[NORTH] && flag_status[SOUTH] && flag_status[EAST] && flag_status[WEST] && flag_status[FLOOR] && flag_status[CEILING])
        return (1);
    return (0);
}

int parse_data(int fd, t_map_info *map_info)
{
    t_read_status	read_status;
    t_read_line read_line;
    char *out_line;
    t_parse_phase parse_phase;
    t_map_builder mb;
    int mb_initialized;

    if (!map_info || fd < 0)
        return (-1);
    
    if (!read_line_init(&read_line, fd))
        return (-1);
    
    parse_phase = PHASE_ELEM;
    mb_initialized = 0;
    
    while(1)
    {
        read_status = read_next_line(&read_line, &out_line);
        if (read_status==RD_BAD_ARGS)
        {
            return (-1);
        }
        else if (read_status==RD_EOF)
        {
            break;
        }
        t_judge_type judge_type;
        judge_type = judge_line(out_line, parse_phase);

        if (parse_phase==PHASE_ELEM)
        {
            if (judge_type==J_EMPTY)
            {
                printf("type: J_EMPTY\nline: %s\n", out_line);
                //handle_empty
                //go to next line
            }
            else if (judge_type == J_ELEM_NO)
            {
                printf("type: J_ELEM_NO\nline: %s\n", out_line);
                //parse north
                int process_texture_ret = process_texture_line(map_info, judge_type, out_line);
                if (process_texture_ret<0)
                {
                    //error: process texture
                    printf("process texture failed!\n");
                    //interrupt parsing
                    free(out_line);
                    return (-1);  
                }
                //set flag after successful processing
                map_info->flag_status.flag_status[NORTH] = true;
            }
            else if (judge_type == J_ELEM_SO)
            {
                printf("type: J_ELEM_SO\nline: %s\n", out_line);
                //parse south
                int process_texture_ret = process_texture_line(map_info, judge_type, out_line);
                if (process_texture_ret<0)
                {
                    //error: process texture
                    printf("process texture failed!\n");
                    //interrupt parsing
                    free(out_line);
                    return (-1);  
                }
                //set flag after successful processing
                map_info->flag_status.flag_status[SOUTH] = true;
            }
            else if (judge_type == J_ELEM_WE)
            {
                printf("type: J_ELEM_WE\nline: %s\n", out_line);
                //parse west
                int process_texture_ret = process_texture_line(map_info, judge_type, out_line);
                if (process_texture_ret<0)
                {
                    //error: process texture
                    printf("process texture failed!\n");
                    //interrupt parsing
                    free(out_line);
                    return (-1);  
                } 
                //set flag after successful processing
                map_info->flag_status.flag_status[WEST] = true;
            }
            else if (judge_type == J_ELEM_EA)
            {
                printf("type: J_ELEM_EA\nline: %s\n", out_line);
                //parse east
                int process_texture_ret = process_texture_line(map_info, judge_type, out_line);
                if (process_texture_ret<0)
                {
                    //error: process texture
                    printf("process texture failed!\n");
                    //interrupt parsing
                    free(out_line);
                    return (-1);  
                }
                //set flag after successful processing
                map_info->flag_status.flag_status[EAST] = true;
            }
            else if (judge_type == J_ELEM_F)
            {
                printf("type: J_ELEM_F\nline: %s\n", out_line);
                //parse Floor
                int process_color_ret = process_color_line(map_info, judge_type, out_line);
                if (process_color_ret<0)
                {
                    printf("process color failed!\n");
                    free(out_line);
                    return (-1);
                }
            }
            else if (judge_type == J_ELEM_C)
            {
                printf("type: J_ELEM_C\nline: %s\n", out_line);
                //parse Ceiling
                int process_color_ret = process_color_line(map_info, judge_type, out_line);
                if (process_color_ret<0)
                {
                    printf("process color failed!\n");
                    free(out_line);
                    return (-1);
                }
            }
            else {
                printf("type: J_INVALID\nline: %s\n", out_line);
                free(out_line);
                return (-1);
                //invalid!
            }
            if (except_map_flags_ok(map_info->flag_status.flag_status))
            {
                parse_phase = PHASE_MAP;
                // Don't initialize map_builder here, wait for first map line
            }
        }
        else {
            if (judge_type==J_MAP_LINE)
            {
                printf("type: J_MAP_LINE\nline: %s\n", out_line);
                
                // Initialize map_builder on first map line
                if (!mb_initialized)
                {
                    map_builder_init(&mb);
                    mb_initialized = 1;
                }
                
                //parse map
                int add_line_ret = map_builder_add_line(&mb, out_line);
                if (add_line_ret<0)
                {
                    free(out_line);
                    if (mb_initialized)
                        map_builder_destroy(&mb);
                    return (-1);
                }
                //set flag
                //parse map
            }
            else if (judge_type==J_EMPTY)
            {
                printf("type: J_EMPTY in MAP phase\nline: %s\n", out_line);
                // Empty lines in map phase are allowed, just skip
            }
            else {
                printf("type: Invalid\nline: %s\n", out_line);//regardless of types.
                free(out_line);
                if (mb_initialized)
                    map_builder_destroy(&mb);
                return (-1);
                //invalid!
            }
        }
        free(out_line);
    }
    if (!mb_initialized)
    {
        printf("No map data found!\n");
        return (-1);
    }
    
    // Save map dimensions before calling map_builder_return_map (which resets them)
    size_t saved_row_size = mb.row_size;
    size_t saved_col_size = mb.col_size;
    
    // if(out_line)
        // free(out_line);
    char **map = map_builder_return_map(&mb);
    if (map==NULL)
    {
        printf("map_builder_return_map failed!\n");
        return (-1);
    }
    
    char *rect_map = map_normalize_rectangle(map, saved_row_size, saved_col_size);
    if (rect_map==NULL)
    {
        printf("map_normalize_rectangle failed!\n");
        free_map(map);
        return (-1);
    }
    
    // Free the 2D map as we now use the normalized 1D map
    free_map(map);
    
    // Store the normalized 1D map in map_info
    map_info->map = rect_map;
    map_info->map_rows = (int)saved_row_size;
    map_info->map_cols = (int)saved_col_size;
    
    int start_point[2];
    start_point[0]=-1;
    start_point[1]=-1;
    char direction;
    int scan_set_start_ret = map_scan_set_start(rect_map, saved_row_size, saved_col_size, start_point, &direction);
    if (scan_set_start_ret<0)
    {
        printf("scan_set_start failed!\n");
        free(rect_map);
        return (-1);
    }
    map_info->flag_status.flag_status[START] = true;
    
    // Replace starting position with '0' for validation
    rect_map[start_point[0] * saved_col_size + start_point[1]] = '0';
    
    int validate_closed_ret;
    validate_closed_ret = map_validate_closed(rect_map, saved_row_size, saved_col_size, start_point[0], start_point[1]);
    if (validate_closed_ret != 1)
    {
        printf("map has fault!\n");
        free(rect_map);
        return (-1);
    }
    map_info->flag_status.flag_status[MAP] = true;
    map_info->start_x = start_point[1];
    map_info->start_y = start_point[0];
    map_info->start_direction = direction;
    
    if (flag_status_ok(map_info))
    {
        printf("flag_status_ok!\n");
        return (1);
    }
    return (-1);
}
