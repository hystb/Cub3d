/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raylength.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:21:08 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/25 13:21:09 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	edit_point(double x, double y, t_coord *point)
{
	if (!point)
		return ;
	point->x = x;
	point->y = y;
}

int	is_wall_touched(t_coord	*point, char **map)
{
	if ((int) point->y < 0 ||(int) point->x < 0)
		return (2);
	if (map[(int) point->y][(int) point->x] == '1')
		return (1);
	return (0);
}

double	depth_horizontal(t_raycast *rcast)
{
	double	distance;
	double	y_hor;
	double	x_hor;

	if (rcast->sin_angle > 0)
		y_hor = (rcast->y_map + 1);
	else
		y_hor = (rcast->y_map - 0.0001);
	distance = (y_hor - rcast->y) / rcast->sin_angle;
	x_hor = rcast->x + distance * rcast->cos_angle;
	edit_point(x_hor, y_hor, rcast->hor);
	return (distance);
}

double	depth_vertical(t_raycast *rcast)
{
	double	distance;
	double	y_vert;
	double	x_vert;

	if (rcast->cos_angle > 0)
		x_vert = (rcast->x_map + 1);
	else
		x_vert = (rcast->x_map - 0.0001);
	distance = (x_vert - rcast->x) / rcast->cos_angle;
	y_vert = rcast->y + distance * rcast->sin_angle;
	edit_point(x_vert, y_vert, rcast->ver);
	return (distance);
}

void	readjust_point(t_coord *point, t_raycast *rcast, int mode)
{
	if (mode)
	{
		if (rcast->sin_angle > 0)
			point->y -= 1;
		else
			point->y += 0.0001;
	}
	else
	{
		if (rcast->cos_angle > 0)
			point->x -= 1;
		else
			point->x += 0.0001;	
	}
}

t_coord	*ray_length(t_raycast *rcast, t_player *p, char **map)
{
	t_coord	*actual;
	rcast->cos_angle = cos(rcast->angle);
	rcast->sin_angle = sin(rcast->angle);
	rcast->x_map = floor(rcast->x);
	rcast->y_map = floor(rcast->y);
	rcast->result = 0;

	actual = p->position;
	while (!is_wall_touched(actual, map))
	{
		if (rcast->angle == 0 || rcast->angle == get_rad(180))
		{
			rcast->result += depth_horizontal(rcast);
			actual = rcast->hor;
			rcast->x = actual->x;
			rcast->y = actual->y;
			rcast->x_map = floor(actual->x);
			rcast->y_map = floor(actual->y);
		}
		if (rcast->angle == get_rad(90) || rcast->angle == get_rad(270))
		{
			rcast->result += depth_vertical(rcast);
			actual = rcast->ver;
			rcast->x = actual->x;
			rcast->y = actual->y;
			rcast->x_map = floor(actual->x);
			rcast->y_map = floor(actual->y);
		}
		else
		{
			rcast->depth_hor = depth_horizontal(rcast);
			rcast->depth_ver = depth_vertical(rcast);
			if (rcast->depth_hor < rcast->depth_ver)
			{
				actual = rcast->hor;
				rcast->result += rcast->depth_hor;
				rcast->x = actual->x;
				rcast->y = actual->y;
				rcast->x_map = floor(actual->x);
				rcast->y_map = floor(actual->y);
			}
			else
			{
				actual = rcast->ver;
				rcast->result += rcast->depth_ver;
				rcast->x = actual->x;
				rcast->y = actual->y;
				rcast->x_map = floor(actual->x);
				rcast->y_map = floor(actual->y);
			}
		}
	}
	if (rcast->angle == 0 || rcast->angle == get_rad(180))
		readjust_point(actual, rcast, 1);
	else if (rcast->angle == get_rad(90) || rcast->angle == get_rad(270))
		readjust_point(actual, rcast, 0);
	else
	{
		if (rcast->depth_hor > rcast->depth_ver)
			readjust_point(actual, rcast, 0);
		else
			readjust_point(actual, rcast, 1);
	}
	rcast->result = rcast->result * cos(p->actual_view - rcast->angle);
	return (actual);
}