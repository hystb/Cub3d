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

t_imgdata	*draw_vertical_line(int width, int height, void *mlx, int color)
{
	t_imgdata	*img;

	img = malloc(sizeof(t_imgdata)); // protection

	img->img = mlx_new_image(mlx, width++, height++);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_line, &img->endian);
	while (--width >= 0)
	{
		while (--height >= 0)
			set_pixel_img(img, width, height, color);
	}
	return (img);
}