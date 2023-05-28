#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "parsing.h"
# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"


# define FOV get_rad(80)
# define SPEED_MOV 0.09
# define SPEED_CAM 0.04
# define WIN_TITLE "Cube3D"

typedef struct s_coord
{
	double x;
	double y;
}				t_coord;

typedef struct	s_imgdata {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_imgdata;

typedef struct s_raycast
{
	t_coord	*hor;
	t_coord	*ver;
	t_coord	*target;
	t_imgdata *imgdata;
	double	end;
	double	x;
	double	y;
	double	x_map;
	double	y_map;
	double	sin_angle;
	double	cos_angle;
	double	angle;
	double	depth_hor;
	double	depth_ver;
	double	depth_box;
	double	result;
}				t_raycast;

typedef struct s_player
{
	t_coord				*position;
	t_raycast			*rcast;
	struct s_game_data	*game;
	void				*mlx_win;
	void				*mlx;
	char				**map;
	double				actual_view;
	double				step;
	double				screen_ratio;
	int					win_x;
	int					win_y;
	int					floor_c;
	int					roof_c;
	int					map_max_x;
	int					map_max_y;
}				t_player;

/* collisions */
int		is_wall_touched(t_coord	*point, char **map);
int		get_face(t_coord *c, t_raycast *rc);

/* mlx	*/
void	draw_vertical_line(t_data_game *data, int size, int x_img, int face);
int		get_color(int r, int g, int b);
int		action(int keycode, t_player *player);

/* math tools */
double 	get_rad(double angle);
int		is_whole_number(double e);
double	get_degrees(double angle);

/* raycasting */
void	edit_point(double x, double y, t_coord *point);
void	render(void *mlx, t_player *p, char **map);
t_coord	*ray_length(t_raycast *rcast, t_player *p, char **map);
int		do_render_loop(struct s_game_data *data);
int		get_texture(int face, int size, int pixel_y, float percentage_face);

/* utils */
void	ft_free(void *ptr);

/* exit */
void	free_exec_struct(t_player *p);

#endif