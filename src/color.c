/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   color.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/12 15:26:33 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/21 14:17:53 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t	interpolate(uint8_t ar, uint8_t br, uint8_t shift, float frac)
{
	return ((uint32_t)(ar + (br - ar) * frac) << shift);
}

static t_rgba	color_gradient(t_rgba c_start, t_rgba c_end, uint32_t step, int32_t len)
{
	t_rgba		color;
	float		fraction;
	const float	increment_step = 1.0f / len;

	fraction = step * increment_step;
	color.value = interpolate(c_start.r, c_end.r, 24, fraction)
		| interpolate(c_start.g, c_end.g, 16, fraction)
		| interpolate(c_start.b, c_end.b, 8, fraction)
		| interpolate(c_start.a, c_end.a, 0, fraction);
	return (color);
}

// t_rgba get_color(t_fdf *fdf, t_color_gradient g, uint32_t step, int32_t len, float start_z, float end_z)
// {
// 	const float		min_z = abs(fdf->map->min_z);
// 	const float		max_z = abs(fdf->map->max_z);
// 	const float		total_z_height = min_z + max_z;
// 	const t_rgba	c_end = { .value = 0x00ffffff};
// 	const t_rgba	c_start = { .value = 0xff00ffff};
// 	t_rgba			start_l;
// 	t_rgba			end_l;
//
// 	if (fdf->projector.active_view.color_mode == COLOR_MODE_HEIGHT)
// 	{
// 		start_z += min_z;
// 		end_z += min_z;
// 		start_l = color_gradient(c_start, c_end, start_z, total_z_height);
// 		end_l = color_gradient(c_start, c_end, end_z, total_z_height);
// 		return (color_gradient(start_l, end_l, step, len));
// 	}
// 	else
// 		return (color_gradient(g.c1, g.c2, step, len));
// }

t_rgba get_color(t_fdf *fdf, t_color_info *info)
{
	const float		min_z = abs(fdf->map->min_z);
	const float		max_z = abs(fdf->map->max_z);
	const float		total_z_height = min_z + max_z;
	const t_rgba	c_end = { .value = 0x00ffffff};
	const t_rgba	c_start = { .value = 0xff00ffff};
	t_rgba			start_l;
	t_rgba			end_l;

	if (fdf->projector.active_view.color_mode == COLOR_MODE_HEIGHT)
	{
		info->start_z += min_z;
		info->end_z += min_z;
		start_l = color_gradient(c_start, c_end, info->start_z, total_z_height);
		end_l = color_gradient(c_start, c_end, info->end_z, total_z_height);
		return (color_gradient(start_l, end_l, info->step, info->len));
	}
	else
		return (color_gradient(info->g.c1, info->g.c2, info->step, info->len));
}
