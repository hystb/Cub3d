#include "../includes/exec.h"

int	is_whole_number(double e)
{
	if (e == floor(e))
		return (1);
	return (0);
}

double	get_distance(t_coord *a, t_coord *b, double angle)
{
	double	distance;

	distance = sqrt(pow((b->x - a->x), 2) + pow((b->y - a->y), 2));
	// angle = fmod(angle, M_PI * 2);
	// angle = get_rad(angle);
	// printf("voici l'angle utilisé pour la correction %f\n", angle);

	return (distance);
	// return (distance * cos(angle));
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
	if ((angle < M_PI_2 && angle >= 0) || (angle < 3 * M_PI / 2 && angle >= M_PI))  
		angle = M_PI_2 - fmod(angle, M_PI_2);
	else
		angle = fmod(angle, M_PI_2);
	return (angle);
}
