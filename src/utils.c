/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/19 23:52:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/20 23:33:46 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>
#include <strings.h>

uint8_t	check_extension(const char *map, const char *ext)
{
	int	map_len;
	int	ext_len;

	map_len = ft_strlen(map);
	ext_len = ft_strlen(ext);
	if (map_len < ext_len + 1)
		return (0);
	return (!ft_strncmp((map + map_len - ext_len), ext, ext_len));
}

uint32_t color_add_alpha(uint32_t c)
{
	uint32_t i = 0;
	uint32_t c_tmp = c;
	while (c_tmp)
	{
		c_tmp /= 16;
		i++;
	}
	while (i < 8) 
	{
		if (i >= 6)
			c = c << 4 | 0xF;
		else
			c = c << 4 | 0x0;
		i++;
	}
	return (c);
}
