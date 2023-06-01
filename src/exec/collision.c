/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:25 by ebillon           #+#    #+#             */
/*   Updated: 2023/06/01 12:25:50 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_block(int x, int y, char **map)
{
	if (map[y][x] == '1' || map[y][x] == '\n' \
	|| map[y][x] == '\0' || map[y][x] == ' ')
		return (1);
	return (0);
}

int	is_wall_touched(t_coord	*point, char **map)
{
	if ((int) point->y < 0 || (int) point->x < 0)
		return (2);
	return (is_block(point->x, point->y, map));
}
