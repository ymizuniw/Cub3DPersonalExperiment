#include <stdio.h>

int	visit(char *map, int row_max, int col_max, int row, int col)
{
	int	found;

    if (row < 0 || col < 0 || row  >= row_max || col  >= col_max)
    {
        return (0);
    }
    if (map[row * col_max + col] == ' ')
        return (0);
    if (map[row * col_max + col]=='1')
        return (0);
    if (row==0 || col==0 || row + 1==row_max || col + 1==col_max)
    {
        if (map[row*col_max + col]=='0')
            return (0);
    }
	found = -1;
	map[row * col_max + col] = 'v';
	if (col + 1 < col_max && map[row*col_max + col + 1]!='1' && map[row*col_max + col + 1]!='v')
		found = visit(map, row_max, col_max, row, col + 1);
	if (found == -1 && col  > 0 && map[row*col_max + col -1]!='1' && map[row*col_max + col -1]!='v')
		found = visit(map, row_max, col_max, row, col - 1);
	if (found == -1 && row + 1 < row_max && map[(row+1)*col_max + col]!='1' && map[(row+1)*col_max + col]!='v')
		found = visit(map, row_max, col_max, row + 1, col);
	if (found == -1 && row > 0 && map[(row-1)*col_max + col]!='1' && map[(row-1)*col_max + col]!='v')
		found = visit(map, row_max, col_max, row - 1, col);
	return (found);
}

int map_validate_closed(char *map, int row_max, int col_max, int row, int col)
{
    int result = visit(map, row_max, col_max, row, col);
    return (result == -1) ? 1 : -1;
}
