#include "../includes/exec.h"

t_coord	*do_first_quarter(double x, double y, double angle)
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
		return (&(t_coord){x + opposite / tan(angle), y - opposite});
	else
		return (&(t_coord){x + adjacent, y - adjacent * tan(angle)});
}

t_coord	*do_second_quarter(double x, double y, double angle)
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
		return (&(t_coord){x + opposite / tan(angle), y + opposite});
	else
		return (&(t_coord){x + adjacent, y + adjacent * tan(angle)});
}

t_coord	*do_third_quarter(double x, double y, double angle)
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
		return (&(t_coord){x - opposite / tan(angle), y + opposite});
	else
		return (&(t_coord){x - adjacent, y + adjacent * tan(angle)});
}

t_coord	*do_last_quarter(double x, double y, double angle)
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
		return (&(t_coord){x - opposite / tan(angle), y - opposite});
	else
		return (&(t_coord){x - adjacent, y - adjacent * tan(angle)});
}

t_coord	*ray_lenght(double x, double y, double angle, char **map)
{
	t_coord	next_touched;

	if (!is_block_touched(x, y, map))
	{
		if (angle < 90)
			next_touched = *do_first_quarter(x, y, get_rad(angle));	
		if (angle >= 90 && angle < 180)
			next_touched = *do_second_quarter(x, y, get_rad(angle));
		if (angle >= 180 && angle < 270)
			next_touched = *do_third_quarter(x, y, get_rad(angle));
		if (angle >= 270 && angle < 360)
			next_touched = *do_last_quarter(x, y, get_rad(angle));
		ray_lenght(next_touched.x, next_touched.y, angle, map);
	}
	else
		return (&(t_coord){x, y});
}