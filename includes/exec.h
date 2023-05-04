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

/* collisions */
int 	get_face(double x, double y, char **map);
int		is_block_touched(double x, double y, char **map);

/* math tools */
double 	get_distance(double xA, double yA, double xB, double yB);
double 	get_rad(double angle);
int		is_whole_number(double e);

/* raycasting */
t_coord *ray_lenght(double x, double y, double angle, char **map);

#endif