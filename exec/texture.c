#include "../includes/exec.h"

int	get_texture(int face, int size, int pixel_y, float percentage_face)
{
	(void) size;
	(void) pixel_y;
	(void) percentage_face;
	return (100 * (face * 2)); // a remplacer par ton truc;
}