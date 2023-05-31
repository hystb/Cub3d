/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:43:41 by nmilan            #+#    #+#             */
/*   Updated: 2023/05/05 13:43:43 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	map_path_is_not_correct(char **map)
{
	ft_putstr_fd("Error\nMap path incorrect\n", 2);
	free_map(map);
	exit (0);
}

void	clean_data(t_data_game data, char *str)
{
	mlx_destroy_image(data.mlx, data.east);
	mlx_destroy_image(data.mlx, data.west);
	mlx_destroy_image(data.mlx, data.north);
	mlx_destroy_image(data.mlx, data.south);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	free_map(data.all_readed);
	if (str)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		exit(1);
	}
	exit(0);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
