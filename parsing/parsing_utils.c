#include "../includes/parsing.h"

void	check_extantion(char *path_map)
{
	int	i;

	i = 0;
	while (path_map[i] != '\0')
		i++;
	if (i > 0 && path_map[i - 1] == 'b')
	{
		if (i - 2 > 0 && path_map[i - 2] == 'u')
		{
			if (i - 3 > 0 && path_map[i - 3] == 'c')
			{
				if (i - 4 > 0 && path_map[i - 4] == '.')
					return ;
			}
		}
	}
	ft_putstr_fd("Error\nExtension of map incorrect", 2);
	exit (0);
}

char	**import_map(const char *file_map)
{
	int		fd;
	char	**map;
	int		map_size;
	int		i;

	map_size = len_column(file_map);
	i = 0;
	map = malloc(sizeof(char *) * (map_size + 1));
	if (!map)
		return (NULL);
	fd = open(file_map, O_RDONLY);
	if (!fd)
		return (NULL);
	map[i++] = get_next_line(fd);
	printf("%s", map[i - 1]);
	if (!map[i - 1] && i > 0)
		map_path_is_not_correct(map);
	while (i < map_size)
	{
		map[i++] = get_next_line(fd);
		printf("%s", map[i - 1]);
		if (!map[i - 1] && i > 0)
			map_path_is_not_correct(map);
	}
	map[i] = NULL;
	return (map);
}


int	len_column(const char *file_map)
{
	int		map_size;
	int		fd;
	char	*line;

	fd = open(file_map, O_RDONLY);
	if (!fd)
		return (0);
	map_size = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		map_size++;
	}
	free(line);
	close(fd);
	return (map_size);
}