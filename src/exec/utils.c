/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:21:39 by ebillon           #+#    #+#             */
/*   Updated: 2023/06/01 12:25:50 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	is_whole_number(float e)
{
	if (e == floor(e))
		return (1);
	return (0);
}

float	get_rad(float angle)
{
	return (angle * M_PI / 180);
}

void	ft_free(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
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

int	get_face(t_coord *c, t_raycast *rc)
{
	float	x;
	float	y;

	x = c->x;
	y = c->y;
	if (!is_whole_number(y) && !is_whole_number(x))
		return (0);
	if (is_whole_number(x))
	{
		if (rc->cos_angle > 0)
			return (2);
		else
			return (4);
	}
	else
	{
		if (rc->sin_angle < 0)
			return (1);
		else
			return (3);
	}
	return (0);
}
