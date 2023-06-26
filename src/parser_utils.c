/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser_utils.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/20 12:41:37 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/26 17:18:15 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>

uint8_t	parser_util_open_map(const char *map)
{
	int	fd;

	if (!check_extension(map, ".fdf"))
		return (!error_message(ERR_MAP_INVALID));
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (!error_print(strerror(errno)));
	return (fd);
}

void	parser_util_add_point(t_fdf *fdf, t_point point)
{
	if (!fdf->map->points_list)
	{
		fdf->map->points_list = lstnew(point);
		fdf->map->points_last = fdf->map->points_list;
	}
	else
		fdf->map->points_last = lstadd_back(&fdf->map->points_last,
				lstnew(point));
}

const char	*parser_map_name(const char *map)
{
	char	*s;

	s = ft_strrchr(map, '/');
	if (s && s + 1)
		return (s + 1);
	return (map);
}
