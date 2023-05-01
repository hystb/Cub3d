#include "includes/parsing.h"

int	main(int argc, char **argv)
{
	t_data_game	data;
	int i = 0;

	if (argc < 2)
		return (write(1, "Error\nNot in off args", 22));
	//peut-etre a enlever
	if (argc > 2)
		return (write(1, "Error\nToo much args", 20));
	//-------
	data = read_map(argv[1], 0, 0);
	while (data.map[i++])
		printf("%s", data.map[i - 1]);
	free_map(data.all_readed);
	free(data.mlx);
	return (0);
}