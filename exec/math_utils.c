#include "../includes/exec.h"

int	is_whole_number(double e)
{
	if (e == floor(e))
		return (1);
	return (0);
}

double	get_distance(double xA, double yA, double xB, double yB)
{
	return (sqrt(pow((xB - xA), 2) + pow((yB - yA), 2)));
}

double	get_rad(double angle)
{
	double	temp;

	if (angle < 90 || (angle >= 180 && angle < 270))
		temp = 90 - (int) angle % 90;
	else
		temp = (int) angle % 90;
	return (temp * M_PI / 180);
}
