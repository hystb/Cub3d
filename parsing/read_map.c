#include "../includes/parsing.h"


void	fill_img(void **img, char *str, t_data_game data)
{
	int	width;
	int	height;

	width = 500;
	height = 500;
	str = &str[3];
	*img = mlx_xpm_file_to_image(data.mlx, str, &width, &height);
	if (!*img)
		return;
		//error to add
	return ;
}

void	fill_rgb(unsigned char *rgb, char *str, t_data_game data)
{
	(void)rgb;
	(void)str;
	(void)data;
	return ;
}

t_data_game	read_map(char *map_path, int i, int map_reached)
{
	t_data_game	data;

	check_extantion(map_path);
	data.all_readed = import_map(map_path);
	data.east = NULL;
	data.map = NULL;
	data.south = NULL;
	data.west = NULL;
	data.north = NULL;
	data.mlx = mlx_init();
	while (data.all_readed[i] && map_reached == 0)
	{
		if (data.all_readed[i][0] == '\n')
			;
		else if (ft_strncmp(data.all_readed[i], "SO", 2) == 0)
			fill_img(&data.south, data.all_readed[i], data);
		else if (ft_strncmp(data.all_readed[i], "NO", 2) == 0)
			fill_img(&data.north, data.all_readed[i], data);
		else if (ft_strncmp(data.all_readed[i], "WE", 2) == 0)
			fill_img(&data.west, data.all_readed[i], data);
		else if (ft_strncmp(data.all_readed[i], "EA", 2) == 0)
			fill_img(&data.east, data.all_readed[i], data);
		else if (ft_strncmp(data.all_readed[i], "C", 1) == 0)
			fill_rgb(data.roof, data.all_readed[i], data);
		else if (ft_strncmp(data.all_readed[i], "F", 1) == 0)
			fill_rgb(data.floor, data.all_readed[i], data);
		else
			map_reached = 1;
		i++;
	}
	data.map = &data.all_readed[i - 1];
	return (data);
}
