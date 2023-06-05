/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:43:52 by nmilan            #+#    #+#             */
/*   Updated: 2023/06/05 12:54:27 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define ERR_RGB "Error\nNo roof or floor set\n"
# define ERR_ASSET "Error\nNo all assets set\n"
# define ERR_CHAR "Error\nNot correct char in the map\n"
# define ERR_SPAWN "Error\nHave more than 1 spawn or 0\n"
# define ERR_CLOSE "Error\nMap not close\n"

typedef struct s_game_data
{
	struct s_player	*p;
	unsigned char	floor[3];
	unsigned char	roof[3];
	int				spawn[3];
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
void		pars_map(t_data_game *data);

//error
void		map_path_is_not_correct(char **map);

//exit
void		free_map(char **map);
void		clean_data(t_data_game data, char *str);

#endif
