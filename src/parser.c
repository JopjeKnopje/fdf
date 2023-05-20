/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                          :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 01:47:41 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/20 02:38:02 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
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

t_color parse_color(const char *s)
{
	char	*delim;
	t_color	color;

	delim = ft_strchr(s, ',');
	if (delim)
		color.c = ft_atoi_hex(delim + 1);
	else
		color.c = 0;
	return color;
}

static uint8_t	parse_line(t_fdf *fdf, const char *line, uint8_t line_count)
{
	char **split;
	t_point point;
	int i;

	split = ft_split(line, ' ');
	if (!split)
		return (error_message(ERR_MALLOC_FAILURE));
	i = 0;
	while (split[i])
	{
		point.x = i;
		point.y = line_count;
		point.z = ft_atoi(split[i]);
		point.color = parse_color(split[i]);
		if (!fdf->map->points)
		{
			fdf->map->points = lstnew(point);
			fdf->map->points_last = fdf->map->points;
		}
		else
			fdf->map->points_last = lstadd_back(&fdf->map->points_last, lstnew(point));
		i++;
	}
	fdf->map->width = i;
	free_split(split);
	return (0);
}

static uint8_t read_map(t_fdf *fdf, int fd)
{
	int i;
	char *line;

	fdf->map = ft_calloc(1, sizeof(t_map));
	if (!fdf->map)
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


uint32_t 	parser(t_fdf *fdf, const char *map)
{
	int fd;

	fd = open_map(map);
	if (!fd)
		return (1);
	if (read_map(fdf, fd))
		return (1);
	close(fd);
	printf("map width %d | map heigth %d\n", fdf->map->width, fdf->map->height);
	return (0);
}
