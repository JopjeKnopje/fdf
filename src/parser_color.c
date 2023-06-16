/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser_color.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/16 02:26:11 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/16 02:27:02 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint32_t 	char_count(const char *s, const char c)
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
	return (c);
}
