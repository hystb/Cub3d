/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:25 by ebillon           #+#    #+#             */
/*   Updated: 2023/06/01 12:25:50 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	move(t_player *p, float axisX, float axisY)
{
	float	x;
	float	y;

	x = p->position->x + axisX * SPEED_MOV;
	y = p->position->y + axisY * SPEED_MOV;
	if (p->map[(int) y][(int) x] == '1')
		return (0);
	else
	{
		p->position->x = x;
		p->position->y = y;
		return (1);
	}
}

static int	cam_move(t_player *p, float value)
{
	float	final_view;

	final_view = p->actual_view;
	final_view += value * SPEED_CAM;
	final_view = final_view + M_PI * 2;
	if (final_view > M_PI * 2)
		final_view = fmod (final_view, M_PI * 2);
	p->actual_view = final_view;
	return (0);
}

static float	m_sin(float angle)
{
	angle += M_PI * 2;
	return (sin(fmod(angle, M_PI * 2)));
}

static float	m_cos(float angle)
{
	angle += M_PI * 2;
	return (cos(fmod(angle, M_PI * 2)));
}

void	update_coordonate(t_player *p)
{
	if (p->c_left)
		cam_move(p, -1);
	if (p->c_right)
		cam_move(p, 1);
	if (p->m_backward)
		move(p, m_cos(p->actual_view + get_rad(180)), m_sin(p->actual_view + get_rad(180)));
	if (p->m_forward)
		move(p, cos(p->actual_view), sin(p->actual_view));
	if (p->m_left)
		move(p, m_cos(p->actual_view - get_rad(90)), m_sin(p->actual_view - get_rad(90)));
	if (p->m_right)
		move(p, m_cos(p->actual_view + get_rad(90)), m_sin(p->actual_view + get_rad(90)));
}

int	action_press(int keycode, t_player *p)
{
	if (keycode == 65307)
		return (free_exec_struct(p, p->game, NULL));
	if (keycode == 65361)
		p->c_left = TRUE;
	if (keycode == 65363)
		p->c_right = TRUE;
	if (keycode == 115)
		p->m_backward = TRUE;
	if (keycode == 119)
		p->m_forward = TRUE;
	if (keycode == 97)
		p->m_left = TRUE;
	if (keycode == 100)
		p->m_right = TRUE;
	return (0);
}

int action_release(int keycode, t_player *p)
{
	if (keycode == 65361)
		p->c_left = FALSE;
	else if (keycode == 65363)
		p->c_right = FALSE;
	else if (keycode == 115)
		p->m_backward = FALSE;
	else if (keycode == 119)
		p->m_forward = FALSE;
	else if (keycode == 97)
		p->m_left = FALSE;
	else if (keycode == 100)
		p->m_right = FALSE;
	return (0);
}