/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   wireframe.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/17 01:56:26 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/17 02:03:57 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void draw_lines(t_fdf *fdf, uint32_t x, uint32_t y)
{
	t_point points[3];


	points[0] = fdf->map->points[y * fdf->map->width + x];
	points[0] = projector(fdf, points[0]);
	if (x + 1 < fdf->map->width)
	{ 
		points[1] = fdf->map->points[y * fdf->map->width + x + 1];
		points[1] = projector(fdf, points[1]);
			if (points_in_window(fdf->image, points[0], points[1]))
				line_draw(fdf, points[0], points[1]);
	}
	if (y + 1 < fdf->map->height)
	{ 
		points[2] = fdf->map->points[(y + 1) * fdf->map->width + x];
		points[2] = projector(fdf, points[2]);
			if (points_in_window(fdf->image, points[0], points[2]))
				line_draw(fdf, points[0], points[2]);
	}
}

void wireframe_draw(t_fdf *fdf)
{
	uint32_t x;
	uint32_t y;

	x = 0;
	while (x < fdf->map->width)
	{
		y = 0;
		while (y < fdf->map->height)
		{
			draw_lines(fdf, x, y);
			y++;
		}
		x++;
	}
}
