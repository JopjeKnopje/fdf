/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   color.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/12 15:26:33 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/14 16:55:58 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


// Find min and max `z` values
// Map min and max to 0 -> 255 called `step`
// For every step in line increment color value with `step`

#include "fdf.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

void color_init(t_fdf *fdf)
{
	// fdf->projector.active_view.color_info;
}

static uint32_t get_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (a << 24 | b << 16 | g << 8 | r);
}


static uint8_t get_color_r(uint32_t c)
{
	return (c);
}

static uint8_t get_color_g(uint32_t c)
{
	return (c >> 8);
}

static uint8_t get_color_b(uint32_t c)
{
	return (c >> 16);
}

static uint8_t get_color_a(uint32_t c)
{
	return (c >> 24);
}

uint32_t interpolate_chan(uint8_t ar, uint8_t br, uint8_t shift, float fracton)
{
	return ((uint32_t) (ar + (br - ar) * fracton) << shift);
}

// Takes c_start and c_end. 
t_rgba color_gradient(t_rgba c_start, t_rgba c_end, uint32_t step, int32_t len)
{
	const float increment_step = 1.0f / len;
	float fraction = 0.0f;

	fraction = step * increment_step;
	
	t_rgba color;
	// color.value	= 	(uint32_t) ((c_end.r - c_start.r) * fraction + c_start.r) << 0 |
	// 				(uint32_t) ((c_end.g - c_start.g) * fraction + c_start.g) << 8 |
	// 				(uint32_t) ((c_end.b - c_start.b) * fraction + c_start.b) << 16 |
	// 				(uint32_t) ((c_end.a - c_start.a) * fraction + c_start.a) << 24;

	color.value	= 	interpolate_chan(c_start.r, c_end.r, 0, fraction) |
				 	interpolate_chan(c_start.g, c_end.g, 8, fraction) |
				 	interpolate_chan(c_start.b, c_end.b, 16, fraction) |
				 	interpolate_chan(c_start.a, c_end.a, 24, fraction);
	return (color);
}
