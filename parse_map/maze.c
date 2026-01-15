#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	count = 0;

int	map[] = {1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 0, 0, 0, 0, 0, 0, 0, 1,
          1, 0, 0, 0,0, 0, 0, 0, 1,
           1, 0, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 1, 
            1,0, 0, 0, 0, 0, 0, 0, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1};

int	visit(int map[], int row_max, int col_max, int row, int col)
{
	int	found;

	printf("info[%03d]: row_max[%d] col_max[%d] (row,col)=(%d,%d)", count++,
		row_max, col_max, row, col);
	printf("(row,col):%d\n", map[row * col_max + col]);
	if ((map[row*col_max + col]==0 && (row == row_max || col == col_max)) || map[row * col_max + col] == 32)
	{
		printf("exit found!\n");
		return (row * col_max + col);
	}

	found = -1;
	map[row * col_max + col] = 1;
	if (col + 1 <= col_max && map[row*col_max + col + 1]!=1)//right
		found = visit(map, row_max, col_max, row, col + 1);
	if (found == -1 && col - 1 >= 0 && map[row*col_max + col -1]!=1)//left
		found = visit(map, row_max, col_max, row, col - 1);
	if (found == -1 && row + 1 <= row_max && map[(row+1)*col_max + col]!=1)
		found = visit(map, row_max, col_max, row + 1, col);
	if (found == -1 && row - 1 >= 0 && map[(row-1)*col_max + col]!=1)//up
		found = visit(map, row_max, col_max, row - 1, col);
	return (found);
}

int	main(void)
{
	int	ret;

	ret = visit(map, 6, 9, 1, 1);
	printf("ret: %d\n", ret);
	return (0);
}
