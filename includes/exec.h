#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "parsing.h"
# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"


# define FOV get_rad(120)
# define SPEED_MOV 0.09
# define SPEED_CAM 0.04
# define WIN_TITLE "Cube3D"

typedef struct s_coord
{
	double x;
	double y;
}				t_coord;

typedef struct s_raycast
{
	t_coord	*hor;
	t_coord	*ver;
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

typedef struct s_player
{
	t_coord		*position;
	t_raycast	*rcast;
	void	*mlx_win;
	void	*mlx;
	char	**map;
	double	actual_view;
	double	step;
	double	screen_ratio;
	int		win_x;
	int		win_y;
	int		map_max_x;
	int		map_max_y;
}				t_player;


typedef struct	s_imgdata {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_imgdata;

/* collisions */
int		is_wall_touched(t_coord	*point, char **map, t_player *player);
int 	get_face(double x, double y, char **map);

/* mlx	*/
void	draw_vertical_line(int height, void *mlx, int color, t_player *p, int i, t_imgdata *img);
int		get_color(int r, int g, int b);
int		action(int keycode, t_player *player);

/* math tools */
double	get_distance(t_coord *a, t_coord *b);
double 	get_rad(double angle);
int		is_whole_number(double e);
double	get_degrees(double angle);

/* raycasting */
void	edit_point(double x, double y, t_coord *point);
void	render(void *mlx, t_player *p, char **map);
t_coord	*ray_length(t_raycast *rcast, t_player *p, char **map);
int		do_render_loop(struct s_game_data *data);

/* utils */
void	ft_free(void *ptr);

/* exit */
void	free_exec_struct(t_player *p);

#endif