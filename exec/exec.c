#include "../includes/exec.h"

void	render(void *mlx, t_player *p, char **map)
{
	double		angle = p->actual_fov - p->fov_size / 2;
	double		end = angle + p->fov_size;
	t_imgdata	*img;
	double		distance;
	double		item_size;
	t_coord 	*touched;
	void		*mlx_win;
	int			i = p->win_x;

	touched = malloc(sizeof(t_coord)); // protection
	// printf("debut %f | fin %f\n", angle, end);
	img = malloc(sizeof(t_imgdata));
	img->img = mlx_new_image(mlx, p->win_x, p->win_y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_line, &img->endian);
	while (angle <= end)
	{
		touched->x = p->position->x;
		touched->y = p->position->y;
		ray_length(M_PI * 2 + angle, map, touched, p);
		distance = get_distance(p->position, touched);
		// distance = distance * sin(M_PI_2 - fmod(angle, M_PI_2)); //correction fisheye
		item_size = p->win_y * (p->screen_ratio / distance);
		if (item_size > p->win_y)
			item_size = p->win_y;
		// printf("Voici la distance %f | la face touchée est %d (x: %f, y: %f) | angle %f, init angle %f \n", distance, get_face(touched->x, touched->y, map), touched->x, touched->y, angle * 180 / M_PI, angle);
		draw_vertical_line(item_size, mlx, get_color(50 * get_face(touched->x, touched->y, map), 100, 0), p, i, img);
		angle += p->step;
		i--;
	}
	mlx_put_image_to_window(mlx, p->mlx_win, img->img, i, 0);
	mlx_destroy_image(mlx, img->img);
	free(img);
	free(touched);
}

void rays(t_player *p, char **map)
{
	double 		angle;
	t_coord 	*touched;
	double		distance;

	touched = malloc(sizeof(t_coord));

	angle = 0 * M_PI / 180;
	double limit = 2 * M_PI;
	while (angle < limit)
	{
		touched->x = p->position->x;
		touched->y = p->position->y;
// 		printf("init x%f y%f \n", touched->x, touched->y);
		ray_length(angle, map, touched, p);
		// printf("init x %f y %f\n", p->position->x, p->position->y);
		// distance = get_distance(p->position, touched);
		// printf("distance = %f | touched x %f y %f (face : %d), angle %f moduled %f\n", distance, touched->x, touched->y, get_face(touched->x, touched->y, map),angle * 180 / M_PI, get_rad(angle) * 180 / M_PI);
		angle += 0.1;
	}
	free(touched);
}

int	action(int keycode, t_player *player)
{
	if (keycode == 65361)
	{
		player->actual_fov += 0.02;
		render(player->mlx, player, player->map);
	}
	else if (keycode == 65363)
	{
		player->actual_fov -= 0.02;
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

	t_player	*player;
	t_coord		position;
	t_imgdata	*img;
	// 0 = droite ?;
	// apres on va vers la droite;
	player = malloc(sizeof(t_player)); // procteciotn

	player->actual_fov = 0 * M_PI / 180;
	player->position = &position;
	player->position->x = 1.5;
	player->position->y = 1.5;
	player->win_x = 1000;
	player->win_y = 800;
	player->fov_size = FOV;
	player->step = player->fov_size / player->win_x;
	player->screen_ratio = player->win_x / 2 / tan(player->fov_size / 2) / player->win_x;
	player->map = map;
	player->map_max_x = ft_strlen(map[1]);
	player->map_max_y = 7;
	// printf("voici le screen ration %f\n", player.screen_ratio);

	rays(player, map);
	// player->mlx = mlx_init();
	// player->mlx_win = mlx_new_window(player->mlx, player->win_x, player->win_y, "Cub3D - Horizon");
	// render(player->mlx, player, map);
	// mlx_hook(player->mlx_win, 2, 1L<<0, &action, player);
	// mlx_loop(player->mlx); //loop here;

	free(map[0]);
	free(map[1]);
	free(map[2]);
	free(map[3]);
	free(map[4]);
	free(map[5]);
	free(map[6]);
	free(map[7]);
	free(player);
}


// to actualize the value of fov and more by getting x and y ;
// mlx_get_screen_size(mlx, &player.win_x, &player.win_y);
