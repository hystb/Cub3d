/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:39 by ebillon           #+#    #+#             */
/*   Updated: 2023/06/01 12:25:50 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

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

int	action_release(int keycode, t_player *p)
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
