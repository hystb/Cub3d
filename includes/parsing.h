#ifndef PARSING_H

# define PARSING_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>


//parsing
int		len_column(const char *file_map);
void	check_extantion(char *path_map);
char	**read_map(char *map_path);
char	**import_map(const char *file_map);

//error
void	map_path_is_not_correct(char **map);

//exit
void	free_map(char **map);

#endif
