/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/19 23:52:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/30 11:25:02 by jboeve        ########   odam.nl         */
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

uint32_t	color_add_alpha(uint32_t c)
{
	uint32_t	i;
	uint32_t	c_tmp;

	c_tmp = c;
	i = 0;
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

uint32_t	list_to_arr(t_fdf *fdf)
{
	const uint32_t	size = fdf->map->width * fdf->map->height;
	t_node			*tmp;
	uint32_t		i;

	fdf->map->points = ft_calloc(sizeof(t_point), size + 1);
	if (!fdf->map->points)
		return (1);
	i = 0;
	tmp = fdf->map->points_list;
	while (tmp && i < size)
	{	
		fdf->map->points[i] = tmp->point;
		tmp = tmp->next;
		i++;
	}
	free_lst(fdf->map->points_list);
	return (0);
}

t_point matmul(t_point point, const float matrix[3][3])
{
	float projx = point.x;
	float projy = point.y;
	float projz = point.z;

	point.x = (projx * matrix[0][0]) + (projy * matrix[0][1]) + (projz * matrix[0][2]);
	point.y = (projx * matrix[1][0]) + (projy * matrix[1][1]) + (projz * matrix[1][2]);
	point.z = (projx * matrix[2][0]) + (projy * matrix[2][1]) + (projz * matrix[2][2]);

	return (point);
}

