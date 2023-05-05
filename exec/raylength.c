#include "../includes/exec.h"

void	do_first_quarter(double x, double y, double angle, t_coord *touched)
{
	double	adjacent;
	double	opposite;
	double	hyp_to_hori;
	double	hyp_to_vert;

	if (x == ceil(x))
		adjacent = 1;
	else
		adjacent = ceil(x) - x;
	hyp_to_vert = adjacent / cos(angle);
	if (y == ceil(y))
		opposite = 1;
	else
		opposite = y - floor(y);
	hyp_to_hori = opposite / sin(angle);
	if (hyp_to_vert > hyp_to_hori)
		set_coord(touched, x + opposite / tan(angle), y - opposite);
	else
		set_coord(touched, x + adjacent, y - adjacent * tan(angle));
}

void	do_second_quarter(double x, double y, double angle, t_coord *touched)
{
	double	adjacent;
	double	opposite;
	double	hyp_to_hori;
	double	hyp_to_vert;

	if (x == ceil(x))
		adjacent = 1;
	else
		adjacent = ceil(x) - x;
	hyp_to_vert = adjacent / cos(angle);
	if (y == ceil(y))
		opposite = 1;
	else
		opposite = ceil(y) - y;
	hyp_to_hori = opposite / sin(angle);
	if (hyp_to_vert > hyp_to_hori)
		set_coord(touched, x + opposite / tan(angle), y + opposite);
	else
		set_coord(touched, x + adjacent, y + adjacent * tan(angle));
}

void	do_third_quarter(double x, double y, double angle, t_coord *touched)
{
	double	adjacent;
	double	opposite;
	double	hyp_to_hori;
	double	hyp_to_vert;

	if (x == ceil(x))
		adjacent = 1;
	else
		adjacent = x - floor(x);
	hyp_to_vert = adjacent / cos(angle);
	if (y == ceil(y))
		opposite = 1;
	else
		opposite = ceil(y) - y;
	hyp_to_hori = opposite / sin(angle);
	if (hyp_to_vert > hyp_to_hori)
		set_coord(touched, x - opposite / tan(angle), y + opposite);
	else
		set_coord(touched, x - adjacent, y + adjacent * tan(angle));
}

void	do_last_quarter(double x, double y, double angle, t_coord *touched)
{
	double	adjacent;
	double	opposite;
	double	hyp_to_hori;
	double	hyp_to_vert;

	if (x == ceil(x))
		adjacent = 1;
	else
		adjacent = x - floor(x);
	hyp_to_vert = adjacent / cos(angle);
	if (y == ceil(y))
		opposite = 1;
	else
		opposite = y - floor(y);
	hyp_to_hori = opposite / sin(angle);
	if (hyp_to_vert > hyp_to_hori)
		set_coord(touched, x - opposite / tan(angle), y - opposite);
	else
		set_coord(touched, x - adjacent, y - adjacent * tan(angle));
}

void	ray_length(double angle, char **map, t_coord *touched)
{
	double	premoduled_angle;
	double	x;
	double	y;

	x = touched->x;
	y = touched->y;
	// printf("les coords x %f y %f | angle %f\n", x, y, angle * 180 / M_PI);
	if (!is_block_touched(x, y, map))
	{
	// 	printf("l'angle qui arrive %f | %f \n", angle * 180 / M_PI, get_rad(angle));
		premoduled_angle = fmod(angle, M_PI * 2);
		// printf("voici l'angle premodulé %f\n", premoduled_angle);
		if (angle < M_PI_2)
		{
			// puts("gauche");
			do_last_quarter(x, y, get_rad(premoduled_angle), touched);
		}
		if (angle >= M_PI_2 && angle < M_PI)
		{
			// puts("bas gauche");
			do_third_quarter(x, y, get_rad(premoduled_angle), touched);
		}
		if (angle >= M_PI && angle < 3 * M_PI / 2)
		{
			// puts("bas droite");
			do_second_quarter(x, y, get_rad(premoduled_angle), touched);	
		}
		if (angle >= 3 * M_PI / 2 && angle < 2 * M_PI)
		{
			// puts("droite");
			do_first_quarter(x, y, get_rad(premoduled_angle), touched);
		}
		ray_length(premoduled_angle, map, touched);
	}
	else
	{
		// printf("final coords x %f y %f | angle %f\n", x, y, angle * 180 / M_PI);	
		set_coord(touched, x, y);
	}
}