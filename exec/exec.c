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

#include "../includes/exec.h"
#include "../includes/parsing.h"

void	render(void *mlx, t_player *p, char **map)
{
	t_raycast 	*rc;
	t_imgdata	*img;
	double		item_size;
	int			x;

	x = 0;
	rc = p->rcast;
	rc->angle = p->actual_view - FOV / 2;
	rc->end = rc->angle + FOV;
	img = rc->imgdata;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return ; // do something here
	while (x < p->win_x)
	{	
		rc->x = p->position->x;
		rc->y = p->position->y;
		rc->target = ray_length(rc, p, map);
		item_size = p->screen_ratio / rc->result;
		if (item_size > p->win_y)
			item_size = p->win_y;
		draw_vertical_line(p->game, item_size, x, get_face(rc->target, rc));
		x++;
		rc->angle = atan((x + 0.00001 - p->win_x / 2) / (p->screen_ratio)) + (p->actual_view);
	}
	mlx_put_image_to_window(mlx, p->mlx_win, img->img, 0, 0);
}

int	malloc_struct(t_data_game *data)
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
		return (free_exec_struct(data->p), 1);
	return (0);
}

/* 1 == width | 0 heigth */
int	get_size_map(int mode, char **map)
{
	int	i;

	if (mode)
		return (ft_strlen(map[0]));
	else
	{
		i = 0;
		while (map[i])
			i++;
		return (i);
	}
}

int	do_render_loop(t_data_game *data)
{
	if (malloc_struct(data))
		free_exec_struct(data->p); // do something else here -> mean that *t_player is not correctly allocated
	data->p->game = data;
	data->p->mlx = data->mlx;
	data->p->win_x = 1000;
	data->p->win_y = 800;
	data->p->rcast->imgdata->img = mlx_new_image(data->mlx, data->p->win_x, data->p->win_y);
	data->win = mlx_new_window(data->mlx, data->p->win_x, data->p->win_y, WIN_TITLE);
	if (!data->mlx || !data->p->rcast->imgdata->img)
		free_exec_struct(data->p); // samething but about mlx win here
	data->p->mlx_win = data->win;
	data->p->actual_view = 0; // add spawn angle from map reading
	data->p->position->x = data->spawn[1];
	data->p->position->y = data->spawn[0];
	data->p->map = data->map;
	data->p->map_max_x = get_size_map(1, data->map);
	data->p->map_max_y = get_size_map(0, data->map);
	data->p->floor_c = get_color(data->floor[0], data->floor[1], data->floor[2]);
	data->p->roof_c = get_color(data->roof[0], data->roof[1], data->roof[2]);

	// this part is to change to fix the little distortion effect !
	data->p->step = FOV / data->p->win_x;
	data->p->screen_ratio = (data->p->win_x / 2) / tan(FOV / 2);
	// end part

	mlx_hook(data->p->mlx_win, 2, 1L<<0, &action, data->p); // movement, need to add "la croix rouge" to close program
	render(data->mlx, data->p, data->map);
	mlx_loop(data->p->mlx);
	return (0);
}
