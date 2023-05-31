/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:44:03 by nmilan            #+#    #+#             */
/*   Updated: 2023/05/05 13:44:04 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	is_all_assets(t_data_game data)
{
	if (!data.east || !data.north || !data.south || !data.west)
	{
		if (data.east)
			mlx_destroy_image(data.mlx, data.east);
		if (data.west)
			mlx_destroy_image(data.mlx, data.west);
		if (data.north)
			mlx_destroy_image(data.mlx, data.north);
		if (data.south)
			mlx_destroy_image(data.mlx, data.south);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		free_map(data.all_readed);
		ft_putstr_fd(ERR_ASSET, STDERR_FILENO);
		exit (1);
	}
	if (data.is_floor == 0 || data.is_roof == 0)
		clean_data(data, ERR_RGB);
}

static void	is_correct_char(char **map, int i, int j, t_data_game *data)
{
	int	spawn;

	spawn = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
			&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
			&& map[i][j] != ' ' && map[i][j] != '\n' && map[i][j] != '\0')
				clean_data(*data, ERR_CHAR);
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				data->spawn[0] = i;
				data->spawn[1] = j;
				spawn++;
			}
			if (spawn > 1)
				clean_data(*data, ERR_SPAWN);
		}
	}
	if (spawn == 0)
		clean_data(*data, ERR_SPAWN);
}

static int	find_end(char **map, char *line)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			i++;
	}
	else if (line)
	{
		while (line[i] && line[i] != '\n')
			i++;
	}
	return (i - 1);
}

static void	is_close_map(char **map, int end_i, int i, t_data_game data)
{
	int	j;
	int	end_j;

	while (map[i])
	{
		j = 0;
		end_j = find_end(NULL, map[i]);
		while (j < end_j)
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || j == 0 || i == end_i || j == end_j)
					clean_data(data, ERR_CLOSE);
				else if (map[i - 1][j] == ' ' || map[i][j + 1] == ' '
				|| map[i][j - 1] == ' ' || map[i + 1][j] == ' ')
					clean_data(data, ERR_CLOSE);
			}
			j++;
		}
		i++;
	}
}

void	pars_map(t_data_game *data)
{
	is_all_assets(*data);
	is_correct_char(data->map, -1, -1, data);
	data->spawn[2] = data->map[data->spawn[0]][data->spawn[1]];
	data->map[data->spawn[0]][data->spawn[1]] = '0';
	is_close_map(data->map, find_end(data->map, NULL), 0, *data);
	data->map[data->spawn[0]][data->spawn[1]] = data->spawn[2];
}
