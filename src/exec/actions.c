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
	if (is_block(x, y, p->map) || is_block(x + 0.1, y - 0.1, p->map) \
	|| is_block(x + 0.1, y + 0.1, p->map) || is_block(x - 0.1, y + 0.1, p->map) \
	|| is_block(x - 0.1, y - 0.1, p->map))
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
		move(p, m_cos(p->actual_view + R_180), \
		m_sin(p->actual_view + R_180));
	if (p->m_forward)
		move(p, cos(p->actual_view), sin(p->actual_view));
	if (p->m_left)
		move(p, m_cos(p->actual_view - R_90), \
		m_sin(p->actual_view - R_90));
	if (p->m_right)
		move(p, m_cos(p->actual_view + R_90), \
		m_sin(p->actual_view + R_90));
}
