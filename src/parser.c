/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.c                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/16 22:23:56 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/16 22:26:02 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

static uint8_t	open_map(const char *map)
{
	int	fd;

	if (!check_extension(map, ".fdf"))
		return (!error_message(ERR_MAP_INVALID));
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (!error_print(strerror(errno)));
	return (fd);
}

static float parse_z(t_map *map, const char *s)
{
	float z;

	z = ft_atoi(s);

	if (z > map->max_z)
		map->max_z = z;
	if (map->min_z)
		map->min_z = z;
	return (z);
}

static uint8_t	parse_line(t_fdf *fdf, const char *line, uint8_t line_count)
{
	char	**split;
	t_point	point;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		return (error_message(ERR_MALLOC_FAILURE));
	i = 0;
	while (split[i])
	{
		point.x = i;
		point.y = line_count;
		point.z = parse_z(fdf->map, split[i]);
		point.color = parse_color(fdf->map, split[i]);
		if (!fdf->map->points_list)
		{
			fdf->map->points_list = lstnew(point);
			fdf->map->points_last = fdf->map->points_list;
		}
		else
			fdf->map->points_last = lstadd_back(&fdf->map->points_last,
					lstnew(point));
		i++;
	}
	fdf->map->width = i;
	free_split(split);
	return (0);
}

static uint8_t map_init(t_fdf *fdf)
{
	fdf->map = ft_calloc(1, sizeof(t_map));
	if (!fdf->map)
		return (0);

	fdf->map->min_z = INT_MAX;
	fdf->map->max_z = INT_MIN;
	return (1);
}

static uint8_t	read_map(t_fdf *fdf, int fd)
{
	int		i;
	char	*line;

	if (!map_init(fdf))
		return (error_message(ERR_MALLOC_FAILURE));
	i = 0;
	line = get_next_line(fd);
	if (!line)
		return (error_message(ERR_MAP_INVALID));
	while (line)
	{
		if (parse_line(fdf, line, i))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	fdf->map->height = i;
	return (0);
}

uint32_t	parser(t_fdf *fdf, const char *map)
{
	int	fd;

	fd = open_map(map);
	if (!fd)
		return (1);
	if (read_map(fdf, fd))
		return (1);
	if (list_to_arr(fdf))
		return (1);
	close(fd);
	fdf->map->name = ft_strrchr(map, '/') + 1;
	return (0);
}
