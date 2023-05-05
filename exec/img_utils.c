#include "../includes/exec.h"

void set_pixel_img(t_imgdata *img, int x, int y, int color)
{
	char	*target;

	target = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)target = color;
}

int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

t_imgdata	*draw_vertical_line(int height, void *mlx, int color, t_player *p)
{
	t_imgdata	*img;
	int			i;
	int			start;

	img = malloc(sizeof(t_imgdata)); // protection

	img->img = mlx_new_image(mlx, 1, p->win_y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_line, &img->endian);
	i = 0;
	start = floor(p->win_y / 2 - height / 2);
	while (i < start)
		set_pixel_img(img, 1, i++, get_color(0, 0, 100));
	while (i < start + height)
		set_pixel_img(img, 1, i++, color);
	while (i < p->win_y)
		set_pixel_img(img, 1, i++, get_color(0, 100, 100));
	return (img);
}