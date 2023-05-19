/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                          :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 01:47:41 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/20 00:05:45 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
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

static uint8_t	parse_line(t_fdf *fdf, const char *line)
{
	char **split;
	char *delim;
	int i;

	split = ft_split(line, ' ');
	if (!split)
		return (1);
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], ','))
		{

		}
		else
		{
		
		}
		printf("[%s]", split[i]);
		i++;
	}
	printf("\n");
	return (0);
}

static uint8_t read_map(t_fdf *fdf, int fd)
{
	int i;
	char *line;

	line = get_next_line(fd);
	if (!line)
		return (error_message(ERR_MAP_INVALID));
	while (line)
	{
		if (parse_line(fdf, line))
		{
			return (1);
		}
		// TODO Check leaks when assigning new gnl
		line = get_next_line(fd);
	}
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

	
	return (0);
}
