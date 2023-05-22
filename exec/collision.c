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
		return (0);
	if (is_whole_number(y))
	{
		if (is_block(x, floor(y) - 1, map))
			return (3);
		else if (is_block(x, floor(y) + 1, map))
			return (1);
	}
	else
	{
		if (is_block(floor(x) - 1, y, map))
			return (2);
		else if (is_block(floor(x) + 1, y, map))
			return (4);
	}
	return (0);
}
