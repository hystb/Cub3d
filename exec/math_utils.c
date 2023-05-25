/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:21:32 by ebillon           #+#    #+#             */
/*   Updated: 2023/05/25 13:21:33 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/exec.h"

int	is_whole_number(double e)
{
	if (e == floor(e))
		return (1);
	return (0);
}

double	get_distance(t_coord *a, t_coord *b)
{
	double	distance;
	t_coord	init;
	int		face;
	
	distance = sqrt(pow((b->x - a->x), 2) + pow((b->y - a->y), 2));
	return (distance);
}

double	get_rad(double angle)
{
	return (angle * M_PI / 180);
}

double	get_degrees(double angle)
{
	return (angle * 180 / M_PI);
}
