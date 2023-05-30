/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:35:39 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/25 13:10:05 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static u_int32_t	*get_texture_data(int face, t_data_game *data)
{
	t_img	*sprite;
	int		bpp;
	int		size_line;
	int		endian;

	if (face == 3)
		sprite = data->south;
	else if (face == 2)
		sprite = data->east;
	else if (face == 1)
		sprite = data->north;
	else
		sprite = data->west;
	return ((u_int32_t *) mlx_get_data_addr(sprite, &bpp, &size_line, &endian));
}

int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_texture(int face, int size, int pixel_y, float percentage_face, t_data_game *data)
{
	u_int32_t	color;
	int			pixel;
	u_int32_t	y;
	u_int32_t	x;
	u_int32_t	*src;

	src = get_texture_data(face, data);
	x = percentage_face * 256;
	y = (256 * pixel_y) / size * 256;
	pixel = x + y;
	color = src[pixel];
	return (color);
}