/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:44:28 by nmilan            #+#    #+#             */
/*   Updated: 2023/06/01 12:25:50 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define R_90 M_PI_2
# define R_180 M_PI
# define SPEED_MOV 0.13
# define SPEED_CAM 0.1
# define WIN_TITLE "Cube3D"
# define MEMORY_ERR "Memory allocation error !\n"
# define FALSE 0
# define TRUE 1

typedef struct s_coord
{
	float	x;
	float	y;
}				t_coord;

typedef struct s_imgdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		ratio_bp;
}				t_imgdata;

typedef struct s_raycast
{
	t_coord		*hor;
	t_coord		*ver;
	t_coord		*target;
	t_imgdata	*imgdata;
	int			face;
	float		x;
	float		y;
	float		x_map;
	float		y_map;
	float		sin_angle;
	float		cos_angle;
	float		angle;
	float		depth_hor;
	float		depth_ver;
	float		depth_box;
	float		result;
}				t_raycast;

typedef struct s_player
{
	t_coord				*position;
	t_raycast			*rcast;
	struct s_game_data	*game;
	void				*mlx_win;
	void				*mlx;
	char				**map;
	float				actual_view;
	float				step;
	float				screen_ratio;
	int					win_x;
	int					win_y;
	int					floor_c;
	int					roof_c;
	int					m_forward;
	int					m_backward;
	int					m_left;
	int					m_right;
	int					c_left;
	int					c_right;
}				t_player;

/* mlx	*/
void	draw_vertical_line(t_data_game *data, int size, int x_img, int face);
int		get_color(int r, int g, int b);
int		action_move(int keycode, t_player *player);
int		action_cam(int keycode, t_player *player);

/* math tools */
float	get_rad(float angle);

/* raycasting */
float	depth_horizontal(t_raycast *rcast);
float	depth_vertical(t_raycast *rcast);
void	reset_coordoonate(t_raycast *rcast, t_coord *actual);
void	readjust_point(t_coord *point, t_raycast *rcast, int mode);
int		do_render_loop(struct s_game_data *data);
int		get_texture(int elems[3], float percentage_face, t_data_game *data);
t_coord	*ray_length(t_raycast *rcast, t_player *p, char **map);

/* utils */
void	ft_free(void *ptr);
void	create_mlx_tools(t_data_game *dg);

/* movements */
void	update_coordonate(t_player *p);
int		is_block(int x, int y, char **map);
int		is_wall_touched(t_coord	*point, char **map);
int		action_press(int keycode, t_player *p);
int		action_release(int keycode, t_player *p);

/* exit */
int		free_exec_struct(t_player *p, t_data_game *data, char *str);

#endif