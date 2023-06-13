/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   color.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/12 15:26:33 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/13 19:22:19 by jboeve        ########   odam.nl         */
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
	uint32_t c = (ar + (br - ar) * fracton);
	return (c << shift);
}

// Takes c_start and c_end. 
uint32_t color_interpolate(uint32_t c_start, uint32_t c_end, uint32_t step, int32_t len)
{
	const float increment_step = 1.0f / len;
	float fraction = 0.0f;

	// printf("fraction %f\n", fraction);
	printf("len %d\n", len);

	fraction = step * increment_step;
	
	uint32_t color =  	(uint32_t) ((get_color_r(c_end) - get_color_r(c_start)) * fraction + get_color_r(c_start)) << 0 |
						(uint32_t) ((get_color_g(c_end) - get_color_g(c_start)) * fraction + get_color_g(c_start)) << 8 |
						(uint32_t) ((get_color_b(c_end) - get_color_b(c_start)) * fraction + get_color_b(c_start)) << 16 |
						(uint32_t) ((get_color_a(c_end) - get_color_a(c_start)) * fraction + get_color_a(c_start)) << 24;

	// uint32_t color = 	interpolate_chan(get_color_r(c_end), get_color_r(c_start), 0, fraction) |
	// 					interpolate_chan(get_color_g(c_end), get_color_g(c_start), 8, fraction) |
	// 					interpolate_chan(get_color_b(c_end), get_color_b(c_start), 16, fraction) |
	// 					interpolate_chan(get_color_a(c_end), get_color_a(c_start), 24, fraction);


	return (color);
}
