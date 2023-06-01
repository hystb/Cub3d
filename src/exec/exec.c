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
	float		item_size;
	int			x;

	x = 0;
	rc = p->rcast;
	rc->angle = p->actual_view - FOV / 2;
	while (x < p->win_x)
	{	
		rc->x = p->position->x;
		rc->y = p->position->y;
		rc->target = ray_length(rc, p, p->map);
		item_size = p->screen_ratio / rc->result;
		draw_vertical_line(p->game, item_size, x, get_face(rc->target, rc));
		x++;
		rc->angle = atan((x + 0.00001 - p->win_x / 2) / \
		(p->screen_ratio)) + (p->actual_view);
	}
	mlx_put_image_to_window(p->mlx, p->mlx_win, rc->imgdata->img, 0, 0);
	return (0);
}

static int	malloc_struct(t_data_game *data)
{
	data->p = malloc(sizeof(t_player));
	if (data->p)
	{
		data->p->position = malloc(sizeof(t_coord));
		data->p->rcast = malloc(sizeof(t_raycast));
		if (data->p->rcast)
		{
			data->p->rcast->hor = malloc(sizeof(t_coord));
			data->p->rcast->ver = malloc(sizeof(t_coord));
			data->p->rcast->imgdata = malloc(sizeof(t_imgdata));
		}
	}
	if (!data->p || !data->p->position || !data->p->rcast || \
	!data->p->rcast->hor || !data->p->rcast->ver || !data->p->rcast->imgdata)
		return (free_exec_struct(data->p, data, MEMORY_ERR), 1);
	data->p->mlx = data->mlx;
	data->p->game = data;
	data->p->win_x = 1920;
	data->p->win_y = 1080;
	return (0);
}

static float	get_spawn_view(int e)
{
	if (e == 'N')
		return (get_rad(270) + 0.0001);
	else if (e == 'E')
		return (0 + 0.0001);
	else if (e == 'S')
		return (get_rad(90) + 0.0001);
	else
		return (get_rad(180) + 0.0001);
}

static int	action_kill(t_player *p)
{
	return (free_exec_struct(p, p->game, NULL));
}

int	do_render_loop(t_data_game *dg)
{
	t_imgdata	*img;

	if (malloc_struct(dg))
		free_exec_struct(dg->p, dg, MEMORY_ERR);
	dg->p->rcast->imgdata->img = mlx_new_image(dg->mlx, \
	dg->p->win_x, dg->p->win_y);
	dg->win = mlx_new_window(dg->mlx, dg->p->win_x, \
	dg->p->win_y, WIN_TITLE);
	if (!dg->mlx || !dg->p->rcast->imgdata->img || !dg->win)
		free_exec_struct(dg->p, dg, MEMORY_ERR);
	dg->p->mlx_win = dg->win;
	dg->p->actual_view = get_spawn_view(dg->spawn[2]);
	dg->p->position->x = dg->spawn[1] + 0.5;
	dg->p->position->y = dg->spawn[0] + 0.5;
	dg->p->map = dg->map;
	dg->p->floor_c = get_color(dg->floor[0], dg->floor[1], dg->floor[2]);
	dg->p->roof_c = get_color(dg->roof[0], dg->roof[1], dg->roof[2]);
	dg->p->screen_ratio = (dg->p->win_x / 2) / tan(FOV / 2);
	img = dg->p->rcast->imgdata;
	img->addr = mlx_get_data_addr(img->img, \
		&img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return (free_exec_struct(dg->p, dg, MEMORY_ERR));
	mlx_hook(dg->p->mlx_win, 2, 1L << 0, &action_move, dg->p);
	mlx_hook(dg->p->mlx_win, 17, 0L, &action_kill, dg->p);
	mlx_loop_hook(dg->p->mlx, &render, dg->p);
	mlx_loop(dg->mlx);
	return (0);
}
