#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "parsing.h"
# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"
# include "../libs/mlx/mlx_int.h"

# define FOV M_PI_2
# define SPEED_MOV 0.3
# define SPEED_CAM 0.15
# define WIN_TITLE "Cube3D"
# define MEMORY_ERR "Memory allocation error !\n"

typedef struct s_coord
{
	double	x;
	double	y;
}				t_coord;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_imgdata;

typedef struct s_raycast
{
	t_coord		*hor;
	t_coord		*ver;
	t_coord		*target;
	t_imgdata	*imgdata;
	double		x;
	double		y;
	double		x_map;
	double		y_map;
	double		sin_angle;
	double		cos_angle;
	double		angle;
	double		depth_hor;
	double		depth_ver;
	double		depth_box;
	double		result;
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
}				t_player;

/* collisions */
int		get_face(t_coord *c, t_raycast *rc);

/* mlx	*/
void	draw_vertical_line(t_data_game *data, int size, int x_img, int face);
int		get_color(int r, int g, int b);
int		action_move(int keycode, t_player *player);
int		action_cam(int keycode, t_player *player);

/* math tools */
double	get_rad(double angle);

/* raycasting */
double	depth_horizontal(t_raycast *rcast);
double	depth_vertical(t_raycast *rcast);
void	reset_coordoonate(t_raycast *rcast, t_coord *actual);
void	readjust_point(t_coord *point, t_raycast *rcast, int mode);
int		do_render_loop(struct s_game_data *data);
void	render(void *mlx, t_player *p, char **map);
int		get_texture(int elems[3], float percentage_face, t_data_game *data);
t_coord	*ray_length(t_raycast *rcast, t_player *p, char **map);

/* utils */
void	ft_free(void *ptr);

/* exit */
int	free_exec_struct(t_player *p, t_data_game *data, char *str);

#endif