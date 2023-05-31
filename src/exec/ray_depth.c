/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_depth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:21:08 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/25 13:21:09 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	edit_point(double x, double y, t_coord *point)
{
	if (!point)
		return ;
	point->x = x;
	point->y = y;
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

void	reset_coordoonate(t_raycast *rcast, t_coord *actual)
{
	rcast->x = actual->x;
	rcast->y = actual->y;
	rcast->x_map = floor(actual->x);
	rcast->y_map = floor(actual->y);
}
