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


// la face touche, taille de l'objet et quel pixel on est, les coordonnes de la face (si 59.61 -> 0.61), 
void	draw_vertical_line(int height, void *mlx, int color, t_player *p, int i_img, t_imgdata *img)
{
	int			i;
	int			start;
	int			c_bottom;
	int			c_top;
	
	c_bottom = get_color(50, 0, 100);
	c_top = get_color(0, 100, 25);

	i = 0;
	start = floor(p->win_y / 2 - height / 2);
	while (i < start)
		set_pixel_img(img, i_img, i++, c_bottom);
	while (i < start + height)
		set_pixel_img(img, i_img, i++, color);
	while (i < p->win_y)
		set_pixel_img(img, i_img, i++, c_top);
}