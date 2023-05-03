#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "../libs/libft/libft.h"

typedef struct s_coord
{
	double x;
	double y;
}				t_coord;

int	isBlock(int x, int y, char **map);
#endif