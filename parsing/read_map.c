#include "../includes/parsing.h"

char	**read_map(char *map_path)
{
	char	**map;

	check_extantion(map_path);
	map = import_map(map_path);

	return (map);

}