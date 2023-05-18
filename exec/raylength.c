#include "../includes/exec.h"

int		is_wall_touched(t_coord	*point, char **map, t_player *player)
{
	if (player->map_max_y < (int) point->y || (int) point->y < 0)
		return (1);
	if (player->map_max_x < (int) point->x || (int) point->x < 0)
		return (1);
	if (map[(int) point->y][(int) point->x] == '1')
		return (1);
	return (0);
}

void	depth_horizontal(t_raycast *rcast, t_player *p, char **map)
{
	double	y_hor;
	double	x_hor;
	double	dx;
	double	dy;

	if (rcast->sin_angle > 0)
	{
		y_hor = (rcast->y_map + 1);
		dy = 1;
	}
	else
	{
		y_hor = (rcast->y_map - 0.0000001);
		dy = -1;
	}
	rcast->depth_hor = (y_hor - rcast->y) / rcast->sin_angle;
	x_hor = rcast->x + rcast->depth_hor * rcast->cos_angle;
	rcast->depth_box = dy / rcast->sin_angle;
	dx = rcast->depth_box * rcast->cos_angle;

	while (rcast->max_steps--)
	{
		if (is_wall_touched(&(t_coord){(int) x_hor, (int) y_hor}, map, p))
			return ;
		x_hor += dx;
		y_hor += dy;
		rcast->depth_hor += rcast->depth_box;
	}
	rcast->hor.x = x_hor;
	rcast->hor.y = y_hor;
}

void	depth_vertical(t_raycast *rcast, t_player *p, char **map)
{
	double	y_vert;
	double	x_vert;
	double	dx;
	double	dy;

	if (rcast->cos_angle > 0)
	{
		x_vert = (rcast->x_map + 1);
		dx = 1;
	}
	else
	{
		x_vert = (rcast->x_map - 0.0000001);
		dx = -1;
	}
	rcast->depth_ver = (x_vert - rcast->x) / rcast->cos_angle;
	y_vert = rcast->y + rcast->depth_ver * rcast->sin_angle;
	rcast->depth_box = dx / rcast->cos_angle;
	dy = rcast->depth_box * rcast->sin_angle;
	while (rcast->max_steps--)
	{
		if (is_wall_touched(&(t_coord){(int) x_vert, (int) y_vert}, map, p))
			return ;
		x_vert += dx;
		y_vert += dy;
		rcast->depth_ver += rcast->depth_box;
	}
	rcast->vert.x = x_vert;
	rcast->vert.y = y_vert;
}


void	ray_length(t_raycast *rcast, t_player *p, char **map, t_coord *touched)
{
	rcast->cos_angle = cos(rcast->angle);
	rcast->sin_angle = sin(rcast->angle);
	rcast->x_map = floor(rcast->x);
	rcast->y_map = floor(rcast->y);
	if (rcast->angle != 0 && rcast->angle != get_rad(180))
		depth_horizontal(rcast, p, map);
	if (rcast->angle != get_rad(90) && rcast->angle != get_rad(270))
		depth_vertical(rcast, p, map);
	if (rcast->angle == 0 || rcast->angle == get_rad(180))
		rcast->depth_hor = rcast->depth_ver + 1;
	else if (rcast->angle == get_rad(90) || rcast->angle == get_rad(270))
		rcast->depth_ver = rcast->depth_hor + 1;

	if (rcast->depth_hor > rcast->depth_ver)
	{
		rcast->result = rcast->depth_ver;
		return (&rcast->vert);
	}
	else
	{
		rcast->result = rcast->depth_hor;
		return (&rcast->hor);
	}
}