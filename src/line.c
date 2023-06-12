/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/22 22:11:03 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/12 19:35:50 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fdf.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>


static int32_t increment(int32_t val)
{
	if (val)
		return (1);
	return (-1);
}

static uint32_t get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (a << 24 | b << 16 | g << 8 | r);
}



static uint32_t interpolate_color(uint32_t step, uint32_t max_steps, int32_t dz)
{
	uint32_t c = 0x0;


	// 0 - 100
	// 0 - 255


	// (min - max / 255) = step


	return (c);

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

	int32_t dz = p_start.z - p_end.z;
	uint32_t step = 0;

	int32_t err = 0;

	if (dx > dy)
		err = (dy - dx) / 2;
	else
		err = (dx - dy) / 2;
	while (x_start != x_end || y_start != y_end)
	{
		tmp.y = y_start;
		tmp.x = x_start;

		// TODO find min/max z values, for the color cap.
		tmp.color = color_interpolate();

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
