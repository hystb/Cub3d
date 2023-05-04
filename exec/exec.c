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
	int			i = 0;

	mlx_win = mlx_new_window(mlx, p->win_x, p->win_y, "Cub3D - Horizon");
	// img = draw_vertical_line(10, 500, mlx, get_color(255, 0, 0));
	// mlx_put_image_to_window(mlx, mlx_win, img->img, 400, 0);
	while (angle <= end)
	{
		touched = ray_length(p->position->x, p->position->y, get_rad(angle), map);
		distance = get_distance(p->position, touched);
		distance = distance * cos(get_rad(angle)); //correction fisheye
		item_size = p->win_y * (p->screen_ratio / distance);
		if (item_size > p->win_y)
			item_size = p->win_y;
		// printf("%f\n", (p->screen_ratio / distance));
		printf("la distance %f angle %f | screen ration %f | item_size %f\n", distance, get_rad(angle) * 180 / M_PI, p->screen_ratio, item_size);
		img	= draw_vertical_line(1, item_size, mlx, get_color(250, 100, 0));
		mlx_put_image_to_window(mlx, mlx_win, img->img, i, floor(p->win_y / 2 - item_size / 2));
		angle += p->step;
		mlx_destroy_image(mlx, img->img);
		free(img);
		i++;
	}
}

int main(void)
{
	char *map[100] = {\
	"111111111111111",\
	"100000000000001",\
	"100000000000001",\
	"100000000000001",\
	"100000000000001",\
	"100000000000001",\
	"111111111111111"};


	t_player	player;
	t_coord		position;
	void		*mlx;
	void		*mlx_win;
	t_imgdata	*img;
	
	player.actual_fov = M_PI_2;
	player.position = &position;
	player.position->x = 5;
	player.position->y = 1;
	player.win_x = 1000;
	player.win_y = 800;
	player.fov_size = FOV;
	player.step = player.fov_size / player.win_x;
	player.screen_ratio = player.win_x / 2 / tan(player.fov_size / 2) / player.win_x;
	// printf("voici le screen ration %f\n", player.screen_ratio);

	mlx = mlx_init();
	render(mlx, &player, map);
	mlx_loop(mlx); // loop here;
}


// to actualize the value of fov and more by getting x and y ;
// mlx_get_screen_size(mlx, &player.win_x, &player.win_y);
