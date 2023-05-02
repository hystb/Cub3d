#include "../includes/parsing.h"

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
		ft_putstr_fd(str, STDERR_FILENO);
	exit (1);
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