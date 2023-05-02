#include "../includes/parsing.h"

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

static void	is_correct_char(char **map, int i, int j, t_data_game data)
{
	int	spawn;

	spawn = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
			&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
			&& map[i][j] != ' ' && map[i][j] != '\n' && map[i][j] != '\0')
				clean_data(data, ERR_CHAR);
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				spawn++;
			if (spawn > 1)
				clean_data(data, ERR_SPAWN);
			j++;
		}
		i++;
	}
	if (spawn == 0)
		clean_data(data, ERR_SPAWN);
}

void	pars_map(t_data_game data)
{
	is_all_assets(data);
	is_correct_char(data.map, 0, 0, data);
}
