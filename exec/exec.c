#include "../includes/exec.h"
#include "../libs/mlx/mlx.h"


void set_pixel_img(t_imgdata *img, int x, int y, int color)
{
	char	*target;

	target = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)target = color;
}

/* rgb represetnation */
int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int main(void)
{
	char *map[10] = {\
	"11111",\
	"10001",\
	"10001",\
	"10001",\
	"11111"};

	void		*mlx;
	void		*mlx_win;
	t_imgdata	img;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 800, "Cub3D - Horizon");
	img.img = mlx_new_image(mlx, 200, 200);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);

	int i = 0;
	int j;
	while (i < 90)
	{
		j = 0;
		while (j < 50)
		{
			set_pixel_img(&img, i, j, get_color(100, 100, 0));
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);
}