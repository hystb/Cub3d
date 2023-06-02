/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayc.c                                            :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:21:39 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/25 13:21:40 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static t_coord	*calc_values(t_raycast *rcast, t_player *p)
{
	rcast->cos_angle = cos(rcast->angle);
	rcast->sin_angle = sin(rcast->angle);
	rcast->x_map = floor(rcast->x);
	rcast->y_map = floor(rcast->y);
	rcast->result = 0;
	return (p->position);
}

static void	actualize_face(t_raycast *rcast, int mode)
{
	if (mode == 0)
	{
		if (rcast->cos_angle > 0)
			rcast->face = 2;
		else
			rcast->face = 4;
	}
	else
	{
		if (rcast->sin_angle < 0)
			rcast->face = 1;
		else
			rcast->face = 3;
	}
}

static t_coord	*do_classic(t_raycast *rcast)
{
	t_coord	*actual;

	rcast->depth_hor = depth_horizontal(rcast);
	rcast->depth_ver = depth_vertical(rcast);
	if (rcast->depth_hor < rcast->depth_ver)
	{
		actual = rcast->hor;
		rcast->result += rcast->depth_hor;
		actualize_face(rcast, 1);
	}
	else
	{
		actual = rcast->ver;
		rcast->result += rcast->depth_ver;
		actualize_face(rcast, 0);
	}
	reset_coordoonate(rcast, actual);
	return (actual);
}

static t_coord	*do_only(t_raycast *rcast, int mode)
{
	t_coord	*actual;

	if (mode)
	{
		rcast->result += depth_horizontal(rcast);
		actual = rcast->hor;
		actualize_face(rcast, 1);
	}
	else
	{
		rcast->result += depth_vertical(rcast);
		actual = rcast->ver;
		actualize_face(rcast, 0);
	}
	reset_coordoonate(rcast, actual);
	return (actual);
}

t_coord	*ray_length(t_raycast *rcast, t_player *p, char **map)
{
	t_coord	*actual;

	actual = calc_values(rcast, p);
	while (!is_wall_touched(actual, map))
	{
		if (rcast->angle == 0 || rcast->angle == R_180)
			actual = do_only(rcast, 1);
		if (rcast->angle == R_90 || rcast->angle == get_rad(270))
			actual = do_only(rcast, 0);
		else
			actual = do_classic(rcast);
	}
	if (rcast->angle == 0 || rcast->angle == R_180)
		readjust_point(actual, rcast, 1);
	else if (rcast->angle == R_90 || rcast->angle == get_rad(270))
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
