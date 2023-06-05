/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:39 by ebillon           #+#    #+#             */
/*   Updated: 2023/06/05 15:02:23 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static u_int32_t	*get_texture_data(int face, t_data_game *data, \
t_img *sprite)
{
	u_int32_t	*content;
	int			bpp;
	int			size_line;
	int			endian;

	if (face == 3)
		sprite = data->south;
	else if (face == 2)
		sprite = data->east;
	else if (face == 1)
		sprite = data->north;
	else
		sprite = data->west;
	content = (u_int32_t *) mlx_get_data_addr(sprite, &bpp, \
	&size_line, &endian);
	return (content);
}

int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_texture(int elems[3], float percentage_face, t_data_game *data, \
u_int32_t color)
{
	t_img		*img;
	int			pixel;
	u_int32_t	y;
	u_int32_t	x;
	u_int32_t	*src;

	if (elems[0] == 3)
		img = data->south;
	else if (elems[0] == 2)
		img = data->east;
	else if (elems[0] == 1)
		img = data->north;
	else
		img = data->west;
	src = get_texture_data(elems[0], data, NULL);
	x = percentage_face * img->width;
	y = (img->height * elems[2]) / elems[1] * img->width;
	pixel = x + y;
	if (img->width * img->height < pixel)
		pixel = (img->width * img->height);
	color = src[pixel];
	return (color);
}
