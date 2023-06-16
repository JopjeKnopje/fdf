/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   color.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/12 15:26:33 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/17 00:42:52 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdint.h>


static uint32_t interpolate_chan(uint8_t ar, uint8_t br, uint8_t shift, float fracton)
{
	return ((uint32_t) (ar + (br - ar) * fracton) << shift);
}


t_rgba color_gradient(t_rgba c_start, t_rgba c_end, uint32_t step, int32_t len)
{
	t_rgba color;
	const float increment_step = 1.0f / len;
	float fraction = 0.0f;

	fraction = step * increment_step;
	
	// color.value	= 	interpolate_chan(c_start.r, c_end.r, 0, fraction) |
	// 			 	interpolate_chan(c_start.g, c_end.g, 8, fraction) |
	// 			 	interpolate_chan(c_start.b, c_end.b, 16, fraction) |
	// 			 	interpolate_chan(c_start.a, c_end.a, 24, fraction);

	color.value	= 	interpolate_chan(c_start.r, c_end.r, 24, fraction) |
				 	interpolate_chan(c_start.g, c_end.g, 16, fraction) |
				 	interpolate_chan(c_start.b, c_end.b, 8, fraction) |
				 	interpolate_chan(c_start.a, c_end.a, 0, fraction);

	return (color);
}


t_rgba get_color(t_fdf *fdf, t_color_gradient g, uint32_t step, int32_t len, float start_z, float end_z)
{
	if (fdf->projector.active_view.color_mode == COLOR_MODE_HEIGHT)
	{
		const float total_z_height = abs(fdf->map->max_z) + abs(fdf->map->min_z);

		printf("total_z_height %f\n", total_z_height);

		const t_rgba C_END = { .value = 0x00ffffff};
		const t_rgba C_START = { .value = 0xff00ffff};

		t_rgba start_l = color_gradient(C_START, C_END, start_z, total_z_height);
		t_rgba end_l = color_gradient(C_START, C_END, end_z, total_z_height);

		print_color(start_l);

		t_rgba c = color_gradient(start_l, end_l, step, len);

		return c;

	}
	else {
		return color_gradient(g.c1, g.c2, step, len);
	
	}
}
