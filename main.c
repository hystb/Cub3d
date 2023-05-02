#include "includes/parsing.h"

int	main(int argc, char **argv)
{
	t_data_game	data;
	int i = 0;

	if (argc < 2)
		return (write(STDERR_FILENO, "Error\nNot in off args", 22));
	//peut-etre a enlever
	if (argc > 2)
		return (write(STDERR_FILENO, "Error\nToo much args", 20));
	//-------
	data = read_map(argv[1], 0, 0);
	while (data.map[i++])
		printf("%s", data.map[i - 1]);
	free_map(data.all_readed);
	mlx_destroy_image(data.mlx, data.east);
	mlx_destroy_image(data.mlx, data.west);
	mlx_destroy_image(data.mlx, data.north);
	mlx_destroy_image(data.mlx, data.south);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}