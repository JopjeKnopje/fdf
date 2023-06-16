/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:39:45 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/16 22:16:52 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

static void draw_clear(t_fdf *fdf)
{
	const uint32_t size = fdf->image->width * fdf->image->height;
	int	i;

	i = 0;
	while (i < size)
	{
 		mlx_put_pixel(fdf->image, i, 0, COLOR_BACKGROUND);
		i++;
	}
}

static uint8_t points_in_window(mlx_image_t *image, t_point p1, t_point p2)
{
	return ((p1.x >= 0 && p1.x < image->width && p1.y >= 0 && p1.y < image->height)
		|| (p2.x >= 0 && p2.x < image->width && p2.y >= 0 && p2.y < image->height));
}

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

static void draw_wireframe(t_fdf *fdf)
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

void fdf_put_pixel(t_fdf *fdf, t_point p)
{
	if (p.x >= 0 && p.x < fdf->image->width && p.y >= 0 && p.y < fdf->image->height)
		mlx_put_pixel(fdf->image, p.x, p.y, p.color.value);
}

void draw_hook(void *param)
{
	t_fdf *fdf = param;
	draw_clear(fdf);
	draw_wireframe(fdf);
}
