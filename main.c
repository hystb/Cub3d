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
	data = read_map(argv[1]);
	while (data.all_readed[i++])
		printf("%s", data.all_readed[i - 1]);
	free_map(data.all_readed);
	return (0);
}