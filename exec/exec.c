#include "../includes/exec.h"

void	launch_rays(double x, double y, char **map)
{
	double	angle;
	t_coord	init;
	t_coord	*touched;

	angle = 0;
	while (angle < 360)
	{
		init = (t_coord) {x, y};
		touched = ray_lenght(x, y, angle, map);
		printf("Angle %f, distance %f\n", angle, get_distance(init.x, init.y, touched->x, touched->y));
		angle++;
	}
}

int main(void)
{
	char *map[10] = {\
	"11111",\
	"10001",\
	"10001",\
	"10001",\
	"11111"};

	double x = 2.5;
	double y = 1.5;
	double t_len = 0;

	// rayLenght(1, 1, 180, map, &t_len);
	// printf("x: %f, y: %f\n", x, y);
	// rayLenght(x, y, 90, map);
	// printf("La longueur du segment %f\n", t_len);
	launch_rays(x, y, map);
	// printf("is block x: %f, y: %f | -> %d\n", x, y, isBlockTouched(x, y, map));
}
