#include "../includes/parsing.h"

void	map_path_is_not_correct(char **map)
{
	ft_putstr_fd("Error\nMap path incorrect", 2);
	free_map(map);
	exit (0);
}
