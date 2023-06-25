/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/22 22:11:03 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/25 23:42:31 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static int32_t	direction(int32_t val)
{
	if (val)
		return (1);
	return (-1);
}

static void	bresenham_move(t_bresenham *line)
{
	if (line->delta.x > line->delta.y)
	{
		line->start.x += line->direction.x;
		line->err += line->delta.y;
		if (line->err * 2 >= line->delta.x)
		{
			line->start.y += line->direction.y;
			line->err -= line->delta.x;
		}
	}
	else
	{
		line->start.y += line->direction.y;
		line->err += line->delta.x;
		if (line->err * 2 >= line->delta.y)
		{
			line->start.x += line->direction.x;
			line->err -= line->delta.y;
		}
	}
}

static void	bresenham(t_fdf *fdf, t_bresenham *line, t_color_info *info)
{
	if (line->delta.x > line->delta.y)
		line->err = (line->delta.y - line->delta.x) / 2;
	else
		line->err = (line->delta.x - line->delta.y) / 2;
	while (line->start.x != line->end.x || line->start.y != line->end.y)
	{
		info->end_z = line->end.z;
		info->start_z = line->start.z;
		fdf_put_pixel(fdf, &line->start, get_color(fdf, info).value);
		bresenham_move(line);
		info->step++;
	}
	fdf_put_pixel(fdf, &line->start, get_color(fdf, info).value);
}

void	line_draw(t_fdf *fdf, t_point p_start, t_point p_end)
{
	t_bresenham		line;
	t_color_info	info;

	line.start.x = p_start.x;
	line.start.y = p_start.y;
	line.start.z = p_start.actual_z;
	line.end.x = p_end.x;
	line.end.y = p_end.y;
	line.end.z = p_end.actual_z;
	line.delta.x = abs(line.start.x - line.end.x);
	line.delta.y = abs(line.start.y - line.end.y);
	line.direction.x = direction(line.end.x - line.start.x > 0);
	line.direction.y = direction(line.end.y - line.start.y > 0);
	info.g.c1 = p_start.color;
	info.g.c2 = p_end.color;
	info.step = 0;
	info.len = sqrt(line.delta.x * line.delta.x + line.delta.y * line.delta.y);
	bresenham(fdf, &line, &info);
}
