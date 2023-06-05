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

double	get_rad(double angle)
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
			point->y = ceil(point->y);
	}
	else
	{
		if (rcast->cos_angle > 0)
			point->x -= 1;
		else
			point->x = ceil(point->x);
	}
}
