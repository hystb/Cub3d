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
	double	dir_vector_x;
	double	dir_vector_y;
	double	d_to_x;
	double	d_to_y;
	double	sx;
	double	sy;

	x = touched->x;
	y = touched->y;
	d_to_x = fabs((1 - (x - floor(x))));
	d_to_y = fabs((1 - (y - floor(y))));
	// printf("les coords x %f y %f | angle %f\n", x, y, angle * 180 / M_PI);
	if (!is_block_touched(x, y, map))
	{
	// 	printf("l'angle qui arrive %f | %f \n", angle * 180 / M_PI, get_rad(angle));
		premoduled_angle = fmod(angle, M_PI * 2);
		dir_vector_x = cos(premoduled_angle);
		dir_vector_y = sin(premoduled_angle);
	}
	else
	{
		// printf("final coords x %f y %f | angle %f\n", x, y, angle * 180 / M_PI);	
		set_coord(touched, x, y);
	}
}