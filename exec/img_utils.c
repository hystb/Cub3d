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

static void	set_pix_img(t_imgdata *img, int x, int y, int color)
{
	char	*target;

	target = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int *) target = color;
}

static float	get_perc_face(int face, t_coord *point)
{
	if (face == 1 || face == 3)
		return (point->x - (int)(point->x));
	else
		return (point->y - (int)(point->y));
}

static void	over_flow_line(t_data_game *data, int size, int x_img, int face)
{
	t_coord		*point;
	int			y;
	int			start;

	point = data->p->rcast->target;
	start = (size - data->p->win_y) / 2;
	y = -1;
	while (y++ < data->p->win_y)
		set_pix_img(data->p->rcast->imgdata, x_img, y, \
		get_texture(face, size, start++, get_perc_face(face, point), data));
}

static void	classic_line(t_data_game *data, int size, int x_img, int face)
{
	t_coord		*point;
	int			y;
	int			start;

	point = data->p->rcast->target;
	y = 0;
	start = floor(data->p->win_y / 2 - size / 2);
	while (y < data->p->win_y)
	{
		if (y < start)
			set_pix_img(data->p->rcast->imgdata, x_img, y, \
			data->p->floor_c);
		else if (y >= start && y < start + size)
			set_pix_img(data->p->rcast->imgdata, x_img, y, \
			get_texture(face, size, y - start, get_perc_face(face, \
			point), data));
		else
			set_pix_img(data->p->rcast->imgdata, x_img, y, data->p->roof_c);
		y++;
	}
}

void	draw_vertical_line(t_data_game *data, int size, int x_img, int face)
{
	if (size > data->p->win_y)
		over_flow_line(data, size, x_img, face);
	else
		classic_line(data, size, x_img, face);
}
