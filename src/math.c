/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   math.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/20 23:01:20 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/20 23:46:23 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int32_t	ft_abs(int32_t n)
{
	if (n < 0)
		n = -n;
	return (n);
}
