/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/19 23:52:49 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/14 18:48:59 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <i386/limits.h>
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

static uint32_t 	char_count(const char *s, const char c)
{
	uint32_t	count;
	int			i;

	i = 0;
	count = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
		i = 2;
	while (s[i])
	{
		if (s[count] == c)
			count++;
		else
		 	return (count);
		i++;
	}
	return (count);
}

t_rgba	color_add_alpha(const char *s)
{
	t_rgba		c;
	uint32_t	i;
	uint32_t	tmp;
	uint32_t	count;

	count = 0;
	tmp = ft_atoi_hex(s);
	c.value = tmp;
	if (ft_strlen(s) > 2)
		count = char_count(s + 2, '0');

	i = 8 - count;
	while (tmp)
	{
		tmp /= 16;
		i--;
	}
	c.value <<= i * 4;
	c.a = 0xFF;
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

t_point matmul(t_point point, t_mat3x3 m)
{
	float px = point.x;
	float py = point.y;
	float pz = point.z;

	point.x = (px * m.data[0][0]) + (py * m.data[0][1]) + (pz * m.data[0][2]);
	point.y = (px * m.data[1][0]) + (py * m.data[1][1]) + (pz * m.data[1][2]);
	point.z = (px * m.data[2][0]) + (py * m.data[2][1]) + (pz * m.data[2][2]);

	return (point);
}

t_mat3x3 mat3x3mul(t_mat3x3 m1, t_mat3x3 m2)
{
	t_mat3x3 res;
	int i;
	int j;
	int k;

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

uint32_t map_find_delta_z(t_fdf *fdf)
{
	int i;
	int32_t max;
	int32_t min;

	i = 0;
	max = 0;
	min = 0;
	while (i < fdf->map->width * fdf->map->height) 
	{
		if (fdf->map->points[i].z < min)
			min = fdf->map->points[i].z;
		else if (fdf->map->points[i].z > max)
			max = fdf->map->points[i].z;
		i++;
	}
	return (abs(max - min));
}
