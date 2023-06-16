/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   color.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/12 15:26:33 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/16 02:41:03 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


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


t_rgba get_color(t_fdf *fdf, t_rgba c_start, t_rgba c_end, uint32_t step, int32_t len)
{
	if (fdf->projector.active_view.color_mode == COLOR_MODE_HEIGHT)
	{
		c_start.value = 0xff00ffff;
		c_end.value = 0x00ffffff;
	}
	return color_gradient(c_start, c_end, step, len);
}
