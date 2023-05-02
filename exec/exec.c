#include "../includes/exec.h"

int	isBlock(int x, int y, char **map)
{
	// printf("%d | %d\n", x, y);
	if (map[y][x] != '0')
		return (1);
	return (0);
}

int	isWholeNumber(double e)
{
	if (e == floor(e))
		return (1);
	return (0);
}

char *getFace(double x, double y, char **map)
{
	if (isWholeNumber(y))
	{
		if (isBlock(x, floor(y - 0.10), map))
			return ("sud");
		else
			return ("nord");
	}
	else
	{
		if (isBlock(floor(x - 0.10), y, map))
			return ("est");
		else
			return ("ouest");
	}
}

double getRad(double angle)
{
	return (angle * M_PI / 180);
}

double get_Distance(double xA, double yA, double xB, double yB)
{
	return (sqrt(pow((xB - xA), 2) + pow((yB - yA), 2)));
}

t_coord *rayLenght(double x, double y, double angle, char **map)
{
	double	adjacent;
	double	opposite;
	double	hyp_to_hori;
	double	hyp_to_vert;


	if (!isBlock(floor(x), floor(y), map))
	{
		if (angle <= 90)
		{
			if (x == ceil(x)) // vertical
				adjacent = 1;
			else
				adjacent = ceil(x) - x;
			hyp_to_vert = adjacent / cos(getRad(angle));
			if (y == ceil(y)) // horizontal
				opposite = 1;
			else
				opposite = y - floor(y);
			hyp_to_hori = opposite / sin(getRad(angle));
			if (hyp_to_vert > hyp_to_hori)
			{
				// calculer avec hori
				// printf("horizontal y - 1 opposite %f\n", opposite);
				x = x + opposite / tan(getRad(angle));
				y = y - opposite;
			}
			else
			{
				// calculer avec verti
				// printf("vertical x + 1 adjacent %f\n", adjacent);;
				x = x + adjacent;
				y = y - adjacent * tan(getRad(angle));
			}
			// printf("x: %f, y: %f\n", x, y);
		}
		rayLenght(x, y, angle, map);
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

	double x = 2.5;
	double y = 2.5;
	double t_len = 0;

	// rayLenght(1, 1, 180, map, &t_len);
	// printf("x: %f, y: %f\n", x, y);
	// rayLenght(x, y, 51, map);
	// printf("La longueur du segment %f\n", t_len);
	launchRays(x, y, map);
}