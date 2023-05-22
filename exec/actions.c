/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:25 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/22 13:35:28 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	action(int keycode, t_player *player)
{
	if (keycode == 65307)
	{
		// quit;
	}
	if (keycode == 65361)
	{
		player->actual_fov -= SPEED_CAM;
		render(player->mlx, player, player->map);
	}
	else if (keycode == 65363)
	{
		player->actual_fov += SPEED_CAM;
		render(player->mlx, player, player->map);
	}
	else if (keycode == 115)
	{
		player->position->x += cos(player->actual_fov + get_rad(180)) * SPEED_MOV;
		player->position->y += sin(player->actual_fov + get_rad(180)) * SPEED_MOV;
		render(player->mlx, player, player->map);
	}
	else if (keycode == 119)
	{
		player->position->x += cos(player->actual_fov) * SPEED_MOV;
		player->position->y += sin(player->actual_fov) * SPEED_MOV;
		render(player->mlx, player, player->map);
	}
	else if (keycode == 97)
	{
		player->position->x += cos(player->actual_fov - get_rad(90)) * SPEED_MOV;
		player->position->y += sin(player->actual_fov - get_rad(90)) * SPEED_MOV;
		render(player->mlx, player, player->map);
	}
	else if (keycode == 100)
	{
		player->position->x += cos(player->actual_fov + get_rad(90)) * SPEED_MOV;
		player->position->y += sin(player->actual_fov + get_rad(90)) * SPEED_MOV;
		render(player->mlx, player, player->map);
	}
}
