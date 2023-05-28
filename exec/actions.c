/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:25 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/25 13:14:42 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	move(t_player *p, double axisX, double axisY)
{
	double	x;
	double	y;

	x = p->position->x + axisX * SPEED_MOV;
	y = p->position->y + axisY * SPEED_MOV;
	if (p->map[(int) y][(int) x] == '1')
		return (0);
	else
	{
		p->position->x = x;
		p->position->y = y;
		render(p->mlx, p, p->map);
		return (1);
	}
}

int	cam_move(t_player *p, double value)
{
	double	final_view;

	final_view = p->actual_view;
	final_view += value * SPEED_CAM;
	final_view = final_view + M_PI * 2;
	if (final_view > M_PI * 2)
		final_view = fmod (final_view, M_PI * 2);
	p->actual_view = final_view;
	render(p->mlx, p, p->map);
	return (0);
}

double	m_sin(double angle)
{
	angle += M_PI * 2;
	return (sin(fmod(angle, M_PI * 2)));
}

double	m_cos(double angle)
{
	angle += M_PI * 2;
	return (cos(fmod(angle, M_PI * 2)));
}


int	action(int keycode, t_player *p)
{
	if (keycode == 65307)
	{
		// quit;
	}
	if (keycode == 65361)
		return (cam_move(p, -1));
	else if (keycode == 65363)
		return (cam_move(p, 1));
	else if (keycode == 115)
		return (move(p, m_cos(p->actual_view + get_rad(180)), m_sin(p->actual_view)));
	else if (keycode == 119)
		return (move(p, cos(p->actual_view), sin(p->actual_view)));
	else if (keycode == 97)
		return (move(p, m_cos(p->actual_view - get_rad(90)), m_sin(p->actual_view - get_rad(90))));
	else if (keycode == 100)
		return (move(p, m_cos(p->actual_view + get_rad(90)), m_sin(p->actual_view + get_rad(90))));
	return (0);
}
