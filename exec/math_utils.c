#include "../includes/exec.h"

int	is_whole_number(double e)
{
	if (e == floor(e))
		return (1);
	return (0);
}

double	get_distance(t_coord *a, t_coord *b)
{
	return (sqrt(pow((b->x - a->x), 2) + pow((b->y - a->y), 2)));
}

double	get_rad(double angle)
{
	// double	temp;

	if (angle < 0)
		angle = angle + M_PI * 2;
	angle = fmod(angle, M_PI * 2);
	if (angle < M_PI_2)
		angle = M_PI_2 - fmod(angle, M_PI_2);
	else
		angle = fmod(angle, M_PI_2);
	return (angle);
}
