#include "../includes/exec.h"

int	is_whole_number(double e)
{
	if (e == floor(e))
		return (1);
	return (0);
}

double	get_distance(t_coord *a, t_coord *b)
{
	double	distance;
	t_coord	init;
	int		face;

	// printf("a %f %f b %f %f angle %f\n");
	// printf("touchée x: %f y: %f | dep x: %f y: %f\n",b->x, b->y, a->x, a->y);
	// face = get_face(b->x, b->y, map);
	// if (face == 1 || face == 3)
		// init.y = a->y;
	// else
	// 	// init.x = a->x;
	distance = sqrt(pow((b->x - a->x), 2) + pow((b->y - a->y), 2));
	return (distance);
}

void	set_coord(t_coord *coord, double x, double y)
{
	coord->x = x;
	coord->y = y;
}

double	get_rad(double angle)
{
	return (angle * M_PI / 180);
}

double	get_degrees(double angle)
{
	return (angle * 180 / M_PI);
}
