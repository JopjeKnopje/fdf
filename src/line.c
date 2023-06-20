/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/22 22:11:03 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/20 12:30:30 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>


static int32_t increment(int32_t val)
{
	if (val)
		return (1);
	return (-1);
}

void line_draw(t_fdf *fdf, t_point p_start, t_point p_end)
{
	t_point tmp;

	tmp.color = p_start.color;
	tmp.z = p_start.z;

	int32_t x_start = p_start.x;
	int32_t y_start = p_start.y;
	int32_t x_end = p_end.x;
	int32_t y_end = p_end.y;

	int32_t dx = abs(x_end - x_start);
	int32_t dy = abs(y_end - y_start);
	int32_t sx = increment(x_end - x_start > 0);
	int32_t sy = increment(y_end - y_start > 0);

	uint32_t step = 0;
	int32_t err = 0;

	const uint32_t len = sqrt(dx*dx + dy*dy);
	t_color_gradient grad;
	grad.c1 = p_start.color;
	grad.c2 = p_end.color;

	if (dx > dy)
	{
		err = (dy - dx) / 2;
	}
	else
	{
		err = (dx - dy) / 2;
	}
	while (x_start != x_end || y_start != y_end)
	{
		tmp.y = y_start;
		tmp.x = x_start;
		tmp.color = get_color(fdf, grad, step, len, p_start.actual_z, p_end.actual_z);
		fdf_put_pixel(fdf, tmp);
		if (dx > dy)
		{
			x_start += sx;
			err += dy;
			if (err * 2 >= dx)
			{
				y_start += sy;
				err -= dx;
			}
		}
		else
		{
			y_start += sy;
			err += dx;
			if (err * 2 >= dy)
			{
				x_start += sx;
				err -= dy;
			}
		}
		step++;
	}
	tmp.x = x_start;
	tmp.y = y_start;
	fdf_put_pixel(fdf, tmp);
}
