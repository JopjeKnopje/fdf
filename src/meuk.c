// this file is for developing only should not be included during evaluation

#include "fdf.h"

void print_point(t_point point)
{
	printf("x: %d, y: %d, z: %d", point.x, point.y, point.z);
	if (point.color.c)
		printf(" c: %x", point.color.c);
	printf("\n");

}

void print_points(t_fdf *fdf)
{
	t_node *tmp = fdf->map->points;
	while (tmp)
	{
		print_point(tmp->point);
		tmp = tmp->next;
	}

}
