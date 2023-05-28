/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:21:18 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/25 13:21:19 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	is_block(int x, int y, char **map)
{
	if (map[y][x] != '0')
		return (1);
	return (0);
}

int	get_face(t_coord *c, t_raycast *rc)
{
	double	x;
	double	y;

	x = c->x;
	y = c->y;
	if (!is_whole_number(y) && !is_whole_number(x))
		return (0);
	if (is_whole_number(y))
	{
		if (rc->sin_angle < 0)
			return (1);
		else
			return (3);
	}
	else
	{
		if (rc->cos_angle > 0)
			return (2);
		else
			return (4);
	}
	return (0);
}
