/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   color.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/12 15:26:33 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/16 00:18:06 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


// Find min and max `z` values
// Map min and max to 0 -> 255 called `step`
// For every step in line increment color value with `step`

#include "fdf.h"
#include "libft.h"
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

// static uint32_t 	char_count(const char *s, const char c)
uint32_t 	char_count(const char *s, const char c)
{
	uint32_t		i;

	i = 0;
	while (*s == ' ')
		s++;
	if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
		s += 2;
	while (s[i] == c)
		i++;
	return (i);
}

t_rgba	color_add_alpha(const char *s)
{
	t_rgba c;
	const uint32_t NIBBLE = 4;
	const uint32_t skip = char_count(s, '0');

	c.value = ft_atoi_hex(s);

	int i = 8 - skip;
	uint32_t tmp = c.value;
	while (tmp)
	{
		tmp /= 16;
		i--;
	}

	c.value <<= NIBBLE * i;
	c.a = 0xff;

	print_color(c);
	return (c);
}

uint32_t interpolate_chan(uint8_t ar, uint8_t br, uint8_t shift, float fracton)
{
	return ((uint32_t) (ar + (br - ar) * fracton) << shift);
}

t_rgba color_gradient(t_rgba c_start, t_rgba c_end, uint32_t step, int32_t len)
{
	const float increment_step = 1.0f / len;
	float fraction = 0.0f;

	fraction = step * increment_step;
	
	t_rgba color;
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
