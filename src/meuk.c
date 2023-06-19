// this file is for developing only should not be included during evaluation

#include "fdf.h"
#include <stdint.h>
#include <stdio.h>

void print_point(t_point point)
{
	printf("x: %f, y: %f, z: %f", point.x, point.y, point.z);
	if (point.color.value != COLOR_POINT_DEFAULT)
		printf(" c: %x", point.color.value);
	printf("\n");

}

void print_points(t_fdf *fdf)
{
	t_node *tmp = fdf->map->points_list;
	while (tmp)
	{
		print_point(tmp->point);
		tmp = tmp->next;
	}

}
void print_points_arr(t_fdf *fdf)
{
	uint32_t i = 0;
	
	while (i <= fdf->map->width * fdf->map->height) 
	{
		print_point(fdf->map->points[i]);
		i++;
	}
}

void mat_print(t_mat3x3 m)
{
	printf("[ %f %f %f ]\n", m.data[0][0], m.data[0][1], m.data[0][2]);
	printf("[ %f %f %f ]\n", m.data[1][0], m.data[1][1], m.data[1][2]);
	printf("[ %f %f %f ]\n", m.data[2][0], m.data[2][1], m.data[2][2]);
}

void print_color(t_rgba c)
{
	printf("hex %x | r: %x (%d), g: %x (%d), b: %x (%d), a: %x (%d)\n", c.value, c.r, c.r, c.g, c.g, c.b, c.g, c.a, c.a);
}


void print_text(t_text_image *t)
{
	printf("x %d y %d s %s\n", t->x, t->y, t->s);
}
