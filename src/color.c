/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   color.c                                            :+:    :+:            */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/12 15:26:33 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/13 09:36:21 by joppe         ########   odam.nl         */
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



uint32_t color_interpolate(uint32_t c_start, uint32_t c_end, uint32_t step, int32_t len)
{
	// printf("len %d\n", len);
	int32_t increment = 255 / len; 

	increment += step;

	return (get_color(increment, 0, 0, 255));



}
