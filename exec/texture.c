#include "../includes/exec.h"

int	get_texture(int face, int size, int pixel_y, float percentage_face, t_data_game *data)
{
	u_int32_t	color;
	t_img		*f;
	int			pixel;
	int			a;
	int			b;
	int			c;
	u_int32_t	y;
	u_int32_t	x;

	f = data->south;
	if (face == 1)
	{
		f = data->south;
	}
	else if (face == 2)
	{
		f = data->east;
	}
	else if (face == 3)
	{
		f = data->north;
	}
	else
	{
		f = data->west;
	}
	
	u_int32_t *src = (u_int32_t *)mlx_get_data_addr(f, &a, &b, &c);
	x = percentage_face * 256;
	y = 256 / size * pixel_y * 256;
	pixel = x + y;
	if (pixel > (256 * 256))
		color = 16777215;
	else
		color = src[pixel];

	return (color); // a remplacer par ton truc;
}