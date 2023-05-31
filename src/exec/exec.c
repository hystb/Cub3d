/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:39 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/25 13:10:05 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parsing.h"

void	render(void *mlx, t_player *p, char **map)
{
	t_raycast	*rc;
	t_imgdata	*img;
	double		item_size;
	int			x;

	x = 0;
	rc = p->rcast;
	rc->angle = p->actual_view - FOV / 2;
	img = rc->imgdata;
	img->addr = mlx_get_data_addr(img->img, \
		&img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return ((void )free_exec_struct(p, p->game, MEMORY_ERR));
	while (x < p->win_x)
	{	
		rc->x = p->position->x;
		rc->y = p->position->y;
		rc->target = ray_length(rc, p, map);
		item_size = p->screen_ratio / rc->result;
		draw_vertical_line(p->game, item_size, x, get_face(rc->target, rc));
		x++;
		rc->angle = atan((x + 0.00001 - p->win_x / 2) / \
		(p->screen_ratio)) + (p->actual_view);
	}
	mlx_put_image_to_window(mlx, p->mlx_win, img->img, 0, 0);
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
	data->p->win_x = 1000;
	data->p->win_y = 800;
	return (0);
}

static double	get_spawn_view(int e)
{
	if (e == 'N')
		return (get_rad(270));
	else if (e == 'E')
		return (0);
	else if (e == 'S')
		return (get_rad(90));
	else
		return (get_rad(180));
}

static int	action_kill(t_player *p)
{
	return (free_exec_struct(p, p->game, NULL));
}

int	do_render_loop(t_data_game *dg)
{
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
	mlx_hook(dg->p->mlx_win, 2, 1L<<0, &action_move, dg->p);
	mlx_hook(dg->p->mlx_win, 17, 0L, &action_kill, dg->p);
	render(dg->mlx, dg->p, dg->map);
	mlx_loop(dg->p->mlx);
	return (0);
}
