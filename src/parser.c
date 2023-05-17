/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 01:47:41 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/17 09:40:27 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

uint8_t check_extension(const char *map, const char *ext)
{
	int i;
	int j;

	i = ft_strlen(map) - 1;
	j = ft_strlen(ext) - 1;
	printf("j: %d | i: %d\n", j, i);
	while (j && ext[j] == map[i])
	{
		j--;
		i--;
	}
	printf("j: %d | i: %d\n", j, i);
	if (!j)
		printf("match\n");
	else
		printf("dont match\n");
	return (!j);
}

uint8_t open_map(const char *map)
{
	int fd;

	// check for map extension
	// open map
	// return fd
	if (!check_extension(map, ".fdf"))
	{
		return (!error_message(ERR_MAP_INVALID));
	}
	// fd = open(map, O_RDONLY);
	// if (fd == -1)
	// {
	// 	return (!error_print(strerror(errno)));
	// }
	return (fd);
}

uint32_t 	parser(const char *map)
{
	int fd;

	fd = open_map(map);
	if (!fd)
	{
		printf("open map failed\n");
		return (1);

	}
	
	return (0);
}
