#include "../includes/parsing.h"

t_data_game	read_map(char *map_path)
{
	t_data_game	data;

	check_extantion(map_path);
	data.all_readed = import_map(map_path);

	return (data);

}