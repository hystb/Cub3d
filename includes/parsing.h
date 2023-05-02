#ifndef PARSING_H

# define PARSING_H

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_game_data
{
	unsigned char	floor[3];
	unsigned char	roof[3];
	int				is_floor;
	int				is_roof;
	void			*south;
	void			*north;
	void			*east;
	void			*west;
	char			**map;
	char			**all_readed;
	void			*mlx;
	void			*win;
}					t_data_game;

//parsing
int			len_column(const char *file_map);
void		check_extantion(char *path_map);
t_data_game	read_map(char *map_path, int i, int map_reached);
char		**import_map(const char *file_map);

//error
void		map_path_is_not_correct(char **map);

//exit
void		free_map(char **map);

#endif
