#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"


# define FOV M_PI_2

typedef struct s_coord
{
	double x;
	double y;
}				t_coord;

typedef struct s_player
{
	t_coord *position;
	double	actual_fov;
	double	fov_size;
	double	step;
	double	screen_ratio;
	int		win_x;
	int		win_y;
}				t_player;

typedef struct	s_imgdata {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_imgdata;

/* collisions */
int 	get_face(double x, double y, char **map);
int		is_block_touched(double x, double y, char **map);

/* mlx draw	*/
t_imgdata	*draw_vertical_line(int width, int height, void *mlx, int color);
int			get_color(int r, int g, int b);

/* math tools */
double	get_distance(t_coord *a, t_coord *b);
double 	get_rad(double angle);
int		is_whole_number(double e);

/* raycasting */
t_coord *ray_length(double x, double y, double angle, char **map);

#endif