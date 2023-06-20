/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/19 23:52:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/20 15:45:19 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>
#include <stdio.h>
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

t_point	mat1x3mul(t_point point, t_mat3x3 m)
{
	const float	px = point.x;
	const float	py = point.y;
	const float	pz = point.z;

	point.x = (px * m.data[0][0]) + (py * m.data[0][1]) + (pz * m.data[0][2]);
	point.y = (px * m.data[1][0]) + (py * m.data[1][1]) + (pz * m.data[1][2]);
	point.z = (px * m.data[2][0]) + (py * m.data[2][1]) + (pz * m.data[2][2]);
	return (point);
}

t_mat3x3	mat3x3mul(t_mat3x3 m1, t_mat3x3 m2)
{
	t_mat3x3	res;
	int			i;
	int			j;
	int			k;

	ft_bzero(&res, sizeof(t_mat3x3));
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			while (k < 3)
			{
				res.data[i][j] += m1.data[i][k] * m2.data[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

uint8_t	points_in_window(mlx_image_t *image, t_point p1, t_point p2)
{
	const uint32_t	width = image->width;
	const uint32_t	height = image->height;

	return ((p1.x >= 0 && p1.x < width && p1.y >= 0 && p1.y < height)
		|| (p2.x >= 0 && p2.x < width && p2.y >= 0 && p2.y < height));
}
