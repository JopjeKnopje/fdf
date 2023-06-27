/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   color.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/12 15:26:33 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/27 15:23:25 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint32_t	interpolate(uint8_t ar, uint8_t br, uint8_t shift, float frac)
{
	return ((uint32_t)(ar + (br - ar) * frac) << shift);
}

static t_rgba	color_gradient(t_rgba c1, t_rgba c2, uint32_t step, int32_t len)
{
	t_rgba		color;
	float		fraction;
	const float	increment_step = 1.0f / len;

	fraction = step * increment_step;
	color.value = interpolate(c1.r, c2.r, 24, fraction)
		| interpolate(c1.g, c2.g, 16, fraction)
		| interpolate(c1.b, c2.b, 8, fraction)
		| interpolate(c1.a, c2.a, 0, fraction);
	return (color);
}

t_rgba	get_color(t_fdf *fdf, t_color_info *info)
{
	const float		min_z = ft_abs(fdf->map->min_z);
	const float		max_z = ft_abs(fdf->map->max_z);
	const t_rgba	c_start = {.value = 0xff00ffff};
	t_rgba			start_l;
	t_rgba			end_l;

	end_l.value = 0x00ffffff;
	if (fdf->projector.active_view.color_mode == COLOR_MODE_HEIGHT)
	{
		info->start_z += min_z;
		info->end_z += min_z;
		start_l = color_gradient(c_start, end_l, info->start_z, min_z + max_z);
		end_l = color_gradient(c_start, end_l, info->end_z, min_z + max_z);
		return (color_gradient(start_l, end_l, info->step, info->len));
	}
	else
		return (color_gradient(info->g.c1, info->g.c2, info->step, info->len));
}
