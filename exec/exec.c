#include "../includes/exec.h"

int	isWholeNumber(double e)
{
	if (e == floor(e))
		return (1);
	return (0);
}

int getFace(double x, double y, char **map)
{
	// printf("%f | %f \n", x, y);
	if (!isWholeNumber(y) && !isWholeNumber(x))
		return (5);
	if (isWholeNumber(y))
	{
		if (isBlock(x, floor(y) - 1, map))
			return (3);
		else
			return (1);
	}
	else
	{
		if (isBlock(floor(x) - 1, y, map))
			return (2);
		else
			return (4);
	}
}

int	isWall(char e)
{
	if (e == '1')
		return (1);
	return (0);
}

int isBlock(int x, int y, char **map)
{
	// printf("le bloc en x %d, y %d | %c\n", x, y, map[x][y]);
	if (map[y][x] != '0')
		return (1);
	return (0);
}

int	isBlockTouched(double x, double y, char **map)
{
	// printf("%f | %f\n", x, y);
	int face;

	face = getFace(x, y, map);
	// printf("la face %d\n", face);
	if (face == 1)
		return (isWall(map[(int) floor(x)][(int) floor(y)]));
	else if (face == 2)
	{
		// printf("les causes de la sortie x : %f y %f :| x %d, y %d\n", x, y, (int) floor(x), (int) floor(y));
		return (isWall(map[(int) floor(x) - 1][(int) floor(y)]));
	}
	else if (face == 3)
	{
		// printf("les causes de la sortie x : %f y %f :| x %d, y %d\n", x, y, (int) floor(x), (int) ceil(y) - 1);
		return (isWall(map[(int) floor(x)][(int) ceil(y) - 1]));
	}
	else if (face == 4)
		return (isWall(map[(int) ceil(x)][(int) floor(y)]));
	else
		return (isWall(map[(int) floor(x)][(int) floor(y)]));
}

double getRad(double angle)
{
	return (angle * M_PI / 180);
}

double get_Distance(double xA, double yA, double xB, double yB)
{
	return (sqrt(pow((xB - xA), 2) + pow((yB - yA), 2)));
}

t_coord *do_first_quarter(double x, double y, double angle)
{
	double	adjacent;
	double	opposite;
	double	hyp_to_hori;
	double	hyp_to_vert;

	if (x == ceil(x)) // vertical
		adjacent = 1;
	else
		adjacent = ceil(x) - x;
	hyp_to_vert = adjacent / cos(angle);
	if (y == ceil(y)) // horizontal
		opposite = 1;
	else
		opposite = y - floor(y);
	hyp_to_hori = opposite / sin(angle);
	if (hyp_to_vert > hyp_to_hori)
		return &(t_coord){x + opposite / tan(angle), y = y - opposite};
	else
		return &(t_coord){x + adjacent, y - adjacent * tan(angle)};
}

t_coord *rayLenght(double x, double y, double angle, char **map)
{
	t_coord	*next_touched;

	if (!isBlockTouched(x, y, map))
	{
		if (angle <= 90)
			next_touched = do_first_quarter(x, y, getRad(angle));	
		rayLenght(next_touched->x, next_touched->y, angle, map);
	}
	else
	{
		// printf("Angle %f | touched x = %f | y = %f\n", angle, x, y);
		return &(t_coord){x, y};
	}
		
}

void	launchRays(double x, double y, char **map)
{
	double 	angle;
	double	len;
	t_coord	init;
	t_coord	*touched;

	angle = 0;
	while (angle <= 90)
	{
		len = 0;
		init = (t_coord) {x, y};
		// printf("init x -> %f | y -> %f\n", init.x, init.y);
		touched = rayLenght(x, y, angle, map);
		// printf("angle %f touched x -> %f | y -> %f\n", angle, touched->x, touched->y);
		printf("Angle %f, distance %f\n", angle, get_Distance(init.x, init.y, touched->x, touched->y));
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

	double x = 1.1;
	double y = 3.9;
	double t_len = 0;

	// rayLenght(1, 1, 180, map, &t_len);
	// printf("x: %f, y: %f\n", x, y);
	// rayLenght(x, y, 2, map);
	// printf("La longueur du segment %f\n", t_len);
	launchRays(x, y, map);
	// printf("is block x: %f, y: %f | -> %d\n", x, y, isBlockTouched(x, y, map));
}