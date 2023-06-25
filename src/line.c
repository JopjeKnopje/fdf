/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/22 22:11:03 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/25 21:29:43 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>


static int32_t direction(int32_t val)
{
	if (val)
		return (1);
	return (-1);
}

void line_draw(t_fdf *fdf, t_point p_start, t_point p_end)
{
	t_vec3 start;
	t_vec3 end;

	t_point tmp;

	start.x = p_start.x;
	start.y = p_start.y;
	start.z = p_start.actual_z;
	end.x = p_end.x;
	end.y = p_end.y;
	end.z = p_end.actual_z;

	int32_t dx = abs(start.x - end.x);
	int32_t dy = abs(start.y - end.y);
	int32_t dir_x = direction(end.x - start.x > 0);
	int32_t dir_y = direction(end.y - start.y > 0);

	uint32_t step = 0;
	int32_t err = 0;

	t_color_info info;
	info.g.c1 = p_start.color;
	info.g.c2 = p_end.color;
	info.step = 0;
	info.len = sqrt(dx * dx + dy * dy);


	if (dx > dy)
	{
		err = (dy - dx) / 2;
	}
	else
	{
		err = (dx - dy) / 2;
	}
	while (start.x != end.x || start.y != end.y)
	{
		info.end_z = p_end.actual_z;
		info.start_z = p_start.actual_z;
		tmp.x = start.x;
		tmp.y = start.y;
		tmp.z = start.z;
		tmp.color = get_color(fdf, &info);
		fdf_put_pixel(fdf, tmp);
		if (dx > dy)
		{
			start.x += dir_x;
			err += dy;
			if (err * 2 >= dx)
			{
				start.y += dir_y;
				err -= dx;
			}
		}
		else
		{
			start.y += dir_y;
			err += dx;
			if (err * 2 >= dy)
			{
				start.x += dir_x;
				err -= dy;
			}
		}
		info.step++;
	}
	fdf_put_pixel(fdf, tmp);
}
