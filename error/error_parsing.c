/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:43:04 by nmilan            #+#    #+#             */
/*   Updated: 2023/05/05 13:43:07 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	map_path_is_not_correct(char **map)
{
	ft_putstr_fd("Error\nMap path incorrect", 2);
	free_map(map);
	exit (0);
}
