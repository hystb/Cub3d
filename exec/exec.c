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

	i = 0;
	raycast = malloc(sizeof(t_raycast)); // protection
	touched = malloc(sizeof(t_coord));
	raycast->angle = p->actual_fov - p->fov_size / 2;
	end = raycast->angle + p->fov_size;
	img = malloc(sizeof(t_imgdata));
	img->img = mlx_new_image(mlx, p->win_x, p->win_y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_line, &img->endian);
	raycast->x = p->position->x;
	raycast->y = p->position->y;
	while (raycast->angle <= end)
	{	
		printf("angle %f\n", get_degrees(raycast->angle));
		touched = ray_length(raycast, p, map);
		// printf("touche %f %f %f %f\n", touched->x, touched->y, get_distance(p->position, touched), raycast->result);
		distance = raycast->result;
		distance = raycast->result * cos(p->actual_fov - raycast->angle);
		item_size = p->win_y * (p->screen_ratio / distance);
		// printf("%f\n", item_size);
		if (item_size > p->win_y)
			item_size = p->win_y;
		// printf("le result %f %f\n", touched->x, touched->y);
		draw_vertical_line(item_size, mlx, get_color(30 * get_face(touched->x, touched->y, map), 20, 20), p, i, img);
		raycast->angle += p->step;
		i++;
		free(touched);
	}
	mlx_put_image_to_window(mlx, p->mlx_win, img->img, 0, 0);
	mlx_destroy_image(mlx, img->img);
	free(img);
	free(raycast);
}

void rays(t_player *p, char **map)
{
	double 		angle;
	double		distance;
	t_raycast	*rcast;
	t_coord		*touched;

	touched = malloc(sizeof(t_coord));
	rcast = malloc(sizeof(t_raycast));

	rcast->angle = 0 * M_PI / 180;
	rcast->x = p->position->x;
	rcast->y = p->position->y;
	double limit = 2 * M_PI;
	while (rcast->angle < limit)
	{
		touched = ray_length(rcast, p, map);
		printf("touched (x %f y %f) | distance %f | depth %f\n", touched->x, touched->y, get_distance(p->position, touched), rcast->result);
		rcast->angle += 0.1;
		// free(touched);
	}
	// free(rcast);
}

int	do_render_loop(t_data_game *data)
{
	t_player
}


int main(void)
{
	t_player	*player;
	t_coord		position;
	t_imgdata	*img;
	// 0 = droite ?;
	// apres on va vers la droite;
	player = malloc(sizeof(t_player)); // procteciotn

	player->actual_fov = 0 * M_PI / 180;
	player->position = &position;
	player->position->x = 2;
	player->position->y = 1.5;
	player->win_x = 800;
	player->win_y = 800;
	player->fov_size = FOV;
	player->step = player->fov_size / player->win_x;
	player->screen_ratio = player->win_x / 2 / tan(player->fov_size / 2) / player->win_x;
	player->map = map;
	player->map_max_x = ft_strlen(map[1]);
	player->map_max_y = 3;

	// rays(player, map);
	player->mlx = mlx_init();
	player->mlx_win = mlx_new_window(player->mlx, player->win_x, player->win_y, "Cub3D");
	render(player->mlx, player, map);
	mlx_hook(player->mlx_win, 2, 1L<<0, &action, player);
	mlx_loop(player->mlx); //loop here;

	free(map[0]);
	free(map[1]);
	free(map[2]);
	free(map[3]);
	// free(map[4]);
	// free(map[5]);
	// free(map[6]);
	// free(map[7]);
	free(player);
}

// to actualize the value of fov and more by getting x and y ;
// mlx_get_screen_size(mlx, &player.win_x, &player.win_y);
