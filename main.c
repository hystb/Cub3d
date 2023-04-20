#include "includes/parsing.h"

int	main(int argc, char **argv)
{
	char	**map;
	int i = 0;

	if (argc < 2)
		return (write(1, "Error\nNot in off args", 22));
	//peut-etre a enlever
	if (argc < 2)
		return (write(1, "Error\nToo much args", 20));
	//-------
	map = read_map(argv[1]);
	while (map[i++])
		printf("%s", map[i - 1]);
	free_map(map);
	return (0);
}