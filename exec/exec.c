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

void rayLenght(double x, double y, double angle, char **map, double *t_len)
{
	double	adjacent;
	double	hyp;

	printf("x: %f, y: %f\n", x, y);
	if (!isBlock(floor(x), floor(y), map))
	{
		if (angle <= 90)
		{
			if (x == ceil(x))
				adjacent = 1;
			else
				adjacent = ceil(x) - x;
			hyp = adjacent / cos(angle * M_PI / 180);
			y = y - adjacent * tan(angle * M_PI / 180);
			x = x + adjacent;
			*t_len = hyp + *t_len;
		}
		rayLenght(x, y, angle, map, t_len);
	}
}

void	launchRays(double x, double y, char **map)
{
	double 	angle;
	double	len;

	angle = 0;
	while (angle <= 60)
	{
		len = 0;
		rayLenght(x, y, angle, map, &len);
		printf("Angle %f, distance %f\n", angle, len);
		angle++;
	}
}

int main(void)
{
	char *map[10] = {\
	"111111111",\
	"100000001",\
	"100000001",\
	"100000001",\
	"111111111"};

	double x = 1.5;
	double y = 3.5;
	double t_len = 0;

	// rayLenght(1, 1, 180, map, &t_len);
	// printf("%f\n", t_len);
	// rayLenght(x, y, 52, map, &t_len);
	launchRays(x, y, map);
}