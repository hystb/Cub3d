#include "../includes/exec.h"

void	render(void *mlx, t_player *p, char **map)
{
	double		angle = p->actual_fov - p->fov_size / 2;
	double		end = angle + p->fov_size;
	double		distance;
	double		item_size;
	t_coord 	*touched;
	t_imgdata 	*img;
	void		*mlx_win;
	int			i = p->win_x;

	touched = malloc(sizeof(t_coord)); // protection
	// printf("debut %f | fin %f\n", angle, end);
	while (angle <= end)
	{
		touched->x = p->position->x;
		touched->y = p->position->y;
		ray_length(M_PI * 2 + angle, map, touched);
		distance = get_distance(p->position, touched, M_PI * 2 + angle);
		// distance = distance * cos(get_rad(fmod(M_PI * 2 + angle, M_PI * 2))); //correction fisheye
		item_size = p->win_y * (p->screen_ratio / distance);
		if (item_size > p->win_y)
			item_size = p->win_y;
		// printf("Voici la distance %f | la face touchée est %d (x: %f, y: %f) | angle %f, init angle %f \n", distance, get_face(touched->x, touched->y, map), touched->x, touched->y, angle * 180 / M_PI, angle);
		img	= draw_vertical_line(item_size, mlx, get_color(50 * get_face(touched->x, touched->y, map), 100, 0), p);
		mlx_put_image_to_window(mlx, p->mlx_win, img->img, i, 0);
		angle += p->step;
		mlx_destroy_image(mlx, img->img);
		free(img);
		i--;
	}
	free(touched);
}

void rays(t_player *p, char **map)
{
	double 		angle;
	t_coord 	*touched;

	touched = malloc(sizeof(t_coord));

	angle = 90 * M_PI / 180;
	// double limit = 2 * M_PI - angle;
	// while (angle < limit)
	// {
		touched->x = p->position->x;
		touched->y = p->position->y;
		printf("init x%f y%f \n", touched->x, touched->y);
		ray_length(M_PI * 2 + angle, map, touched);
		// printf("distance = %f | touched x %f y %f (face : %d), angle %f moduled %f\n", get_distance(p->position, touched), touched->x, touched->y, get_face(touched->x, touched->y, map),angle * 180 / M_PI, get_rad(angle) * 180 / M_PI);
		angle += 0.1;
	// }
	free(touched);
}

int	action(int keycode, t_player *player)
{
	if (keycode == 65361)
	{
		puts("gauceh");
		player->actual_fov += 0.05;
		render(player->mlx, player, player->map);
	}
	else if (keycode == 65363)
	{
		player->actual_fov -= 0.05;
		render(player->mlx, player, player->map);
	}
	else if (keycode == 115)
	{
		player->position->y -= 0.1;
		render(player->mlx, player, player->map);
	}
	else if (keycode == 119)
	{
		player->position->y += 0.1;
		render(player->mlx, player, player->map);
	}
}

int main(void)
{
	char *map[20] = {\
	ft_strdup("1111111111"),\
	ft_strdup("1000000001"),\
	ft_strdup("1000000001"),\
	ft_strdup("1000000001"),\
	ft_strdup("1000000001"),\
	ft_strdup("1000000001"),\
	ft_strdup("1000000001"),\
	ft_strdup("1111111111")};
	// ft_strdup("1000000001"),\
	// ft_strdup("1000000001"),\
	// ft_strdup("1000000001"),\
	// ft_strdup("1000000001"),\
	// ft_strdup("1000000001"),\

	t_player	*player;
	t_coord		position;
	t_imgdata	*img;
	// 0 = droite ?;
	// apres on va vers la droite;
	player = malloc(sizeof(t_player)); // procteciotn

	player->actual_fov = 90 * M_PI / 180;
	player->position = &position;
	player->position->x = 6.5;
	player->position->y = 4.5;
	player->win_x = 1000;
	player->win_y = 800;
	player->fov_size = FOV;
	player->step = player->fov_size / player->win_x;
	player->screen_ratio = player->win_x / 2 / tan(player->fov_size / 2) / player->win_x;
	player->map = map;
	// printf("voici le screen ration %f\n", player.screen_ratio);

	// rays(player, map);
	player->mlx = mlx_init();
	player->mlx_win = mlx_new_window(player->mlx, player->win_x, player->win_y, "Cub3D - Horizon");
	render(player->mlx, player, map);
	mlx_key_hook(player->mlx_win, &action, player);
	mlx_loop(player->mlx); //loop here;

	free(map[0]);
	free(map[1]);
	free(map[2]);
	free(map[3]);
	free(player);
}


// to actualize the value of fov and more by getting x and y ;
// mlx_get_screen_size(mlx, &player.win_x, &player.win_y);
