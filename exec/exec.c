/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:39 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/22 14:32:16 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"

void	render(void *mlx, t_player *p, char **map)
{
	t_coord		*touched;
	t_raycast 	*raycast;
	t_imgdata	*img;
	void		*mlx_win;
	double		distance;
	double		item_size;
	double		end;
	double		i;

	// printf("x %f y %f\n", p->position->x, p->position->y);
	i = 0;
	raycast = p->rcast;
	raycast->angle = p->actual_view - FOV / 2;
	end = raycast->angle + FOV;
	img = malloc(sizeof(t_imgdata));
	img->img = mlx_new_image(mlx, p->win_x, p->win_y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_line, &img->endian);
	raycast->x = p->position->x;
	raycast->y = p->position->y;
	while (raycast->angle <= end)
	{	
		raycast->x = p->position->x;
		raycast->y = p->position->y;
		// printf("angle %f\n", get_degrees(raycast->angle));
		touched = ray_length(raycast, p, map);
		// printf("touche %f %f %f %f\n", touched->x, touched->y, get_distance(p->position, touched), raycast->result);
		distance = raycast->result;
		item_size = p->win_y * (p->screen_ratio / distance);
		if (item_size > p->win_y)
			item_size = p->win_y;
		draw_vertical_line(item_size, mlx, get_color(30 * 10, 20, 20), p, i, img);
		// raycast->angle += atan(p->win_x/2 - (raycast->angle - 0.5));
		raycast->angle += p->step;
		i++;
	}
	mlx_put_image_to_window(mlx, p->mlx_win, img->img, 0, 0);
	mlx_destroy_image(mlx, img->img);
	free(img);
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
		}
	}
	if (!data->p || !data->p->position || !data->p->rcast || !data->p->rcast->hor || !data->p->rcast->ver)
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
	data->p->mlx = data->mlx;
	data->p->win_x = 1000;
	data->p->win_y = 800;
	data->win = mlx_new_window(data->mlx, data->p->win_x, data->p->win_y, WIN_TITLE);
	if (!data->mlx)
		free_exec_struct(data->p); // samething but about mlx win here
	data->p->mlx_win = data->win;
	data->p->actual_view = 0; // add spawn angle from map reading
	data->p->position->x = data->spawn[1];
	data->p->position->y = data->spawn[0];
	data->p->map = data->map;
	data->p->map_max_x = get_size_map(1, data->map);
	data->p->map_max_y = get_size_map(0, data->map);

	// this part is to change to fix the little fish eye effect !
	// data->p->step = atan(tan(FOV / 2) / (data-> p->win_x / 2.0));
	data->p->step = FOV / data->p->win_x;
	data->p->screen_ratio = data->p->win_x / 2 / tan(FOV / 2) / data->p->win_x;
	// end part

	mlx_hook(data->p->mlx_win, 2, 1L<<0, &action, data->p); // movement, need to add "la croix rouge" to close program
	render(data->mlx, data->p, data->map);
	mlx_loop(data->p->mlx);
}
