/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:21:27 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/25 13:21:28 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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

float	get_perc_face(int face, t_coord *point)
{
	if (face == 1 || face == 3)
	{
		return (point->x - (int)(point->x));
		// x interessant
	}
	else
	{
		return (point->y - (int)(point->y));
		// y interesant
	}
}

// la face touche, taille de l'objet et quel pixel on est, les coordonnes de la face (si 59.61 -> 0.61), 
void	draw_vertical_line(t_data_game *data, int size, int x_img, int face)
{
	t_coord		*point;
	int			y;
	int			start;

	point = data->p->rcast->target;
	y = -1;
	start = floor(data->p->win_y / 2 - size / 2);
	while (++y < start)
		set_pixel_img(data->p->rcast->imgdata, x_img, y, data->p->floor_c);
	while (++y < start + size)
		set_pixel_img(data->p->rcast->imgdata, x_img, y, get_texture(face, size, y, get_perc_face(face, point)));
	while (++y < data->p->win_y)
		set_pixel_img(data->p->rcast->imgdata, x_img, y, data->p->roof_c);
}