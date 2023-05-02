#include "../includes/parsing.h"


void	fill_img(void **img, char *str, t_data_game data)
{
	int		width;
	int		height;
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	str = &str[3];
	while (str[i] && str[i] != '\n')
		i++;
	str[i] = '\0';
	*img = mlx_xpm_file_to_image(data.mlx, str, &width, &height);
	str[i] = '\n';
	str = tmp;
	return ;
}

void	fill_rgb(unsigned char *rgb, char *str, int *data)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = str;
	str = &str[2];
	while (i < 3)
	{
		j = 0;
		while (str[j] && str[j] != ',')
			j++;
		str[j] = '\0';
		rgb[i] = ft_atoi(str);
		str[j] = ',';
		str = &str[j + 1];
		i++;
	}
	*data = 1;
	str = tmp;
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
	data.is_floor = 0;
	data.is_roof = 0;
	data.mlx = mlx_init();
	if (!data.mlx)
		exit (1);
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
			fill_rgb(data.roof, data.all_readed[i], &data.is_roof);
		else if (ft_strncmp(data.all_readed[i], "F", 1) == 0)
			fill_rgb(data.floor, data.all_readed[i], &data.is_floor);
		else
			map_reached = 1;
		i++;
	}
	data.map = &data.all_readed[i - 1];
	return (data);
}
