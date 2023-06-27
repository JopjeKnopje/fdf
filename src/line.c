/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/22 22:11:03 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/27 13:25:19 by jboeve        ########   odam.nl         */
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
		line->current.x += line->direction.x;
		line->slow_move += line->delta.y;
		if (line->slow_move * 2 >= line->delta.x)
		{
			line->current.y += line->direction.y;
			line->slow_move -= line->delta.x;
		}
	}
	else
	{
		line->current.y += line->direction.y;
		line->slow_move += line->delta.x;
		if (line->slow_move * 2 >= line->delta.y)
		{
			line->current.x += line->direction.x;
			line->slow_move -= line->delta.y;
		}
	}
}

static void	bresenham(t_fdf *fdf, t_bresenham *line, t_color_info *info)
{
	if (line->delta.x > line->delta.y)
		line->slow_move = (line->delta.y - line->delta.x) / 2;
	else
		line->slow_move = (line->delta.x - line->delta.y) / 2;
	while (line->current.x != line->end.x || line->current.y != line->end.y)
	{
		info->end_z = line->end.z;
		info->start_z = line->current.z;
		fdf_put_pixel(fdf, &line->current, get_color(fdf, info).value);
		bresenham_move(line);
		info->step++;
	}
	fdf_put_pixel(fdf, &line->current, get_color(fdf, info).value);
}

void	line_draw(t_fdf *fdf, t_point p_start, t_point p_end)
{
	t_bresenham		line;
	t_color_info	info;

	line.current.x = p_start.x;
	line.current.y = p_start.y;
	line.current.z = p_start.actual_z;
	line.end.x = p_end.x;
	line.end.y = p_end.y;
	line.end.z = p_end.actual_z;
	line.delta.x = abs(line.current.x - line.end.x);
	line.delta.y = abs(line.current.y - line.end.y);
	line.direction.x = direction(line.end.x - line.current.x > 0);
	line.direction.y = direction(line.end.y - line.current.y > 0);
	info.g.c1 = p_start.color;
	info.g.c2 = p_end.color;
	info.step = 0;
	info.len = sqrt(line.delta.x * line.delta.x + line.delta.y * line.delta.y);
	bresenham(fdf, &line, &info);
}
