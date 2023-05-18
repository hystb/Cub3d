#include "../includes/exec.h"

int		is_wall_touched(t_coord	*point, char **map, t_player *player)
{
	if (player->map_max_y < (int) point->y || (int) point->y < 0)
		return (1);
	if (player->map_max_x < (int) point->x || (int) point->x < 0)
		return (1);
	if (map[(int) point->y][(int) point->x] == '1')
		return (1);
	return (0);
}

void	ray_length(double angle, char **map, t_coord *touched, t_player *player)
{
	double MAX_STEPS = 200 * 2;
	double	x;
	double	y;
	double	x_map;
	double	y_map;
	double	cos_a, sin_a;
	double 	dx;
	double	dy;
	double	x_vert, y_vert;
	double 	x_hor, y_hor;
	double	depth_vert, depth_hor, depth_case;

	x = touched->x;
	y = touched->y;
	x_map = floor(x);
	y_map = floor(y);
	// printf("les coords x %f y %f | angle %f\n", x, y, angle * 180 / M_PI);
	if (!is_block_touched(x, y, map))
	{
	// 	printf("l'angle qui arrive %f | %f \n", angle * 180 / M_PI, get_rad(angle));
		cos_a = cos(angle);
		sin_a = sin(angle);
		if (angle != 0 && angle != get_rad(180))
		{
			// horizontal part (y)
			if (sin_a > 0)
			{
				y_hor = (y_map + 1);
				dy = 1;
			}
			else
			{
				y_hor = (y_map - 0.0000001);
				dy = -1;
			}
			depth_hor = (y_hor - y) / sin_a;
			x_hor = x + depth_hor * cos_a;

			depth_case = dy / sin_a;
			dx = depth_case * cos_a;
			// printf("le dx %f dy %f delta%f\n", dx , dy, depth_case);
			while (MAX_STEPS--)
			{
				if (is_wall_touched(&(t_coord){(int) x_hor, (int) y_hor}, map, player))
					break;
				x_hor += dx;
				y_hor += dy;
				depth_hor += depth_case;
			}
		}

		if (angle != get_rad(90) && angle != get_rad(270))
		{
			// vertical part (x)
			if (cos_a > 0)
			{
				x_vert = (x_map + 1);
				dx = 1;
			}
			else
			{
				x_vert = (x_map - 0.0000001);
				dx = -1;
			}
			depth_vert = (x_vert - x) / cos_a;
			y_vert = y + depth_vert * sin_a;

			depth_case = dx / cos_a;
			dy = depth_case * sin_a;
			while (MAX_STEPS--)
			{
				if (is_wall_touched(&(t_coord){(int) x_vert, (int) y_vert}, map, player))
					break;
				x_vert += dx;
				y_vert += dy;
				depth_vert += depth_case;
			}
		}
		// end vertical part
		if (angle == 0 || angle == get_rad(180))
			depth_hor = depth_vert + 1;
		else if (angle == get_rad(90) || angle == get_rad(270))
			depth_vert = depth_hor + 1;
		if (depth_hor > depth_vert)
		{
			// puts("ver");
			printf("angle %f | touched x %f y %f | d %f\n", get_degrees(angle), x_vert, y_vert, depth_vert);
		}
		else
		{
			// puts("hor");
			printf("angle %f | touched x %f y %f | d %f\n", get_degrees(angle), x_hor, y_hor, depth_hor);
		}
	}
	else
	{
		// printf("final coords x %f y %f | angle %f\n", x, y, angle * 180 / M_PI);	
		set_coord(touched, x, y);
	}
}