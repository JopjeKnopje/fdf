/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/19 23:52:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/20 00:53:45 by joppe         ########   odam.nl         */
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
