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
	// printf("le rad qui arrive %f\n", angle);
	// if (angle < 0)
		// angle = angle + M_PI * 2;
	// if ((angle < M_PI_2 && angle >= 0) || (angle < 3 * M_PI / 2 && angle >= M_PI))  
		// angle = M_PI_2 - fmod(angle, M_PI_2);
	// else
		angle = fmod(angle, M_PI_2);
	return (angle);
}
