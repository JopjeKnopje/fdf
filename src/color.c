/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   color.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/12 15:26:33 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/13 14:19:03 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


// Find min and max `z` values
// Map min and max to 0 -> 255 called `step`
// For every step in line increment color value with `step`

#include "fdf.h"
#include <stdint.h>
#include <stdio.h>

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
	return (c >> 24);
}

static uint8_t get_color_g(uint32_t c)
{
	return (c >> 16);
}

static uint8_t get_color_b(uint32_t c)
{
	return (c >> 8);
}

static uint8_t get_color_a(uint32_t c)
{
	return (c);
}

// Takes c_start and c_end. 
uint32_t color_interpolate(uint32_t c_start, uint32_t c_end, uint32_t step, int32_t len)
{

	// Result = (color2 - color1) * fraction + color1

	// step is 0, 255
	const float step_size = 255.0f / len;

	step *= step_size;

	uint32_t color = get_color(step, 0, 0, 255);

	return (color);
}
