#include "../includes/exec.h"

t_coord	*c_point(double x, double y)
{
	t_coord *point;

	point = malloc(sizeof(t_coord));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

void	edit_point(double x, double y, t_coord *point)
{
	if (!point)
		return ;
	point->x = x;
	point->y = y;
}

int	is_wall_touched(t_coord	*point, char **map, t_player *player)
{
	if (player->map_max_y < (int) point->y || (int) point->y < 0)
		return (2);
	if (player->map_max_x < (int) point->x || (int) point->x < 0)
		return (2);
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
	int		check;

	if (rcast->sin_angle > 0)
	{
		y_hor = (rcast->y_map + 1);
		dy = 1;
	}
	else
	{
		y_hor = (rcast->y_map - 0.0001);
		dy = -1;
	}
	rcast->depth_hor = (y_hor - rcast->y) / rcast->sin_angle;
	x_hor = rcast->x + rcast->depth_hor * rcast->cos_angle;
	rcast->depth_box = dy / rcast->sin_angle;
	dx = rcast->depth_box * rcast->cos_angle;
	while (rcast->max_steps--)
	{
		check = is_wall_touched(&(t_coord){(int) x_hor, (int) y_hor}, map, p);
		if (check == 2)
			rcast->depth_hor = INT_MAX;
		if (check)
			break ;
		x_hor += dx;
		y_hor += dy;
		rcast->depth_hor += rcast->depth_box;
	}
	edit_point(x_hor, y_hor, rcast->hor);
}

void	depth_vertical(t_raycast *rcast, t_player *p, char **map)
{
	double	y_vert;
	double	x_vert;
	double	dx;
	double	dy;
	int		check;

	if (rcast->cos_angle > 0)
	{
		x_vert = (rcast->x_map + 1);
		dx = 1;
	}
	else
	{
		x_vert = (rcast->x_map - 0.0001);
		dx = -1;
	}
	rcast->depth_ver = (x_vert - rcast->x) / rcast->cos_angle;
	y_vert = rcast->y + rcast->depth_ver * rcast->sin_angle;
	rcast->depth_box = dx / rcast->cos_angle;
	dy = rcast->depth_box * rcast->sin_angle;
	while (rcast->max_steps--)
	{
		check = is_wall_touched(&(t_coord){(int) x_vert, (int) y_vert}, map, p);
		if (check == 2)
			rcast->depth_ver == INT_MAX;
		if (check)
			break ;
		x_vert += dx;
		y_vert += dy;
		rcast->depth_ver += rcast->depth_box;
	}
	edit_point(x_vert, y_vert, rcast->ver);
}

void	readjust_point(t_coord *point, t_raycast *rcast, int mode)
{
	if (mode)
	{
		if (rcast->sin_angle < 0)
			point->y -= 1;
		else
			point->y += 0.0001;
	}
	else
	{
		if (rcast->cos_angle < 0)
			point->x -= 1;
		else
			point->x += 0.0001;	
	}
}


t_coord	*ray_length(t_raycast *rcast, t_player *p, char **map)
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
		rcast->result = rcast->result * cos(p->actual_view - rcast->angle);
		readjust_point(rcast->ver, rcast, 0);
		return (rcast->ver);
	}
	else
	{
		rcast->result = rcast->depth_hor;
		rcast->result = rcast->result * cos(p->actual_view - rcast->angle);
		readjust_point(rcast->hor, rcast, 1);
		return (rcast->hor);
	}
}