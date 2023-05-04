#include "../includes/exec.h"

int	is_block(int x, int y, char **map)
{
	if (map[y][x] != '0')
		return (1);
	return (0);
}

int	get_face(double x, double y, char **map)
{
	if (!is_whole_number(y) && !is_whole_number(x))
		return (5);
	if (is_whole_number(y))
	{
		if (is_block(x, floor(y) - 1, map))
			return (3);
		else
			return (1);
	}
	else
	{
		if (is_block(floor(x) - 1, y, map))
			return (2);
		else
			return (4);
	}
}

int	is_wall(char e)
{
	if (e == '1')
		return (1);
	return (0);
}

int	is_block_touched(double x, double y, char **map)
{
	int face;

	face = get_face(x, y, map);
	if (face == 1)
		return (is_wall(map[(int) floor(x)][(int) floor(y)]));
	else if (face == 2)
		return (is_wall(map[(int) floor(x) - 1][(int) floor(y)]));
	else if (face == 3)
		return (is_wall(map[(int) floor(x)][(int) ceil(y) - 1]));
	else if (face == 4)
		return (is_wall(map[(int) ceil(x)][(int) floor(y)]));
	else
		return (is_wall(map[(int) floor(x)][(int) floor(y)]));
}
