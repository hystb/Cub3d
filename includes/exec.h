#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"


# define FOV get_rad(70)
# define SPEED_MOV 0.09
# define SPEED_CAM 0.04

typedef struct s_coord
{
	double x;
	double y;
}				t_coord;

typedef struct s_player
{
	t_coord *position;
	void	*mlx_win;
	void	*mlx;
	char	**map;
	double	actual_fov;
	double	fov_size;
	double	step;
	double	screen_ratio;
	int		win_x;
	int		win_y;
	int		map_max_x;
	int		map_max_y;
}				t_player;

typedef struct s_raycast
{
	double	max_steps;
	double	x;
	double	y;
	double	x_map;
	double	y_map;
	double	sin_angle;
	double	cos_angle;
	double	angle_view;
	double	angle;
	double	depth_hor;
	double	depth_ver;
	double	depth_box;
	double	result;
}				t_raycast;


typedef struct	s_imgdata {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_imgdata;

/* collisions */
int 	get_face(double x, double y, char **map);

/* mlx	*/
void	draw_vertical_line(int height, void *mlx, int color, t_player *p, int i, t_imgdata *img);
int		get_color(int r, int g, int b);
int		action(int keycode, t_player *player);

/* math tools */
double	get_distance(t_coord *a, t_coord *b);
double 	get_rad(double angle);
void	set_coord(t_coord *coord, double x, double y);
int		is_whole_number(double e);
double	get_degrees(double angle);

/* raycasting */
void	render(void *mlx, t_player *p, char **map);
t_coord	*ray_length(t_raycast *rcast, t_player *p, char **map);

#endif