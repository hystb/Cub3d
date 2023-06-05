/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:39 by ebillon           #+#    #+#             */
/*   Updated: 2023/06/01 12:25:50 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parsing.h"

int	render(t_player *p)
{
	t_raycast	*rc;
	double		item_size;
	int			x;

	update_coordonate(p);
	x = 0;
	rc = p->rcast;
	rc->angle = p->actual_view - FOV / 2;
	while (x < p->win_x)
	{	
		rc->x = p->position->x;
		rc->y = p->position->y;
		rc->target = ray_length(rc, p, p->map);
		item_size = p->screen_ratio / rc->result;
		draw_vertical_line(p->game, item_size, x, rc->face);
		x++;
		rc->angle = atan((x + 0.0001 - p->win_x / 2) / \
		(p->screen_ratio)) + (p->actual_view) + 0.0001;
	}
	mlx_put_image_to_window(p->mlx, p->mlx_win, rc->imgdata->img, 0, 0);
	return (0);
}

static int	action_kill(t_player *p)
{
	return (free_exec_struct(p, p->game, NULL));
}

int	do_render_loop(t_data_game *dg)
{
	t_imgdata	*img;

	create_mlx_tools(dg);
	img = dg->p->rcast->imgdata;
	img->addr = mlx_get_data_addr(img->img, \
		&img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return (free_exec_struct(dg->p, dg, MEMORY_ERR));
	img->ratio_bp = img->bits_per_pixel / 8;
	mlx_hook(dg->p->mlx_win, 2, 1L << 0, &action_press, dg->p);
	mlx_hook(dg->p->mlx_win, 3, 1L << 1, &action_release, dg->p);
	mlx_hook(dg->p->mlx_win, 17, 0L, &action_kill, dg->p);
	mlx_loop_hook(dg->p->mlx, &render, dg->p);
	mlx_loop(dg->mlx);
	return (0);
}
