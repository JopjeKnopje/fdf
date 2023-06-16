/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   matrices.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/30 12:02:30 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/16 22:01:46 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

const t_mat3x3	get_matrix_rotate_x(float angle)
{
	const t_mat3x3 mat = {
		{
			{1, 0, 0},
			{0, cos(angle), -sin(angle)},
			{0, sin(angle), cos(angle)},
		}
	};
	return (mat);
}

const t_mat3x3	get_matrix_rotate_y(float angle)
{
	const t_mat3x3 mat = {
		{
			{cos(angle), 0, sin(angle)},
			{0, 1, 0},
			{-sin(angle), 0, cos(angle)},
		}
	};
	return (mat);
}

const t_mat3x3	get_matrix_rotate_z(float angle)
{
	const t_mat3x3 mat = {
		{
			{cos(angle), -sin(angle), 0},
			{sin(angle), cos(angle), 0},
			{0, 0, 1},
		}
	};
	return (mat);
}

const t_mat3x3	get_matrix_ortho()
{
	const t_mat3x3 mat = {
		{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 0},
		}
	};
	return (mat);
}

const t_mat3x3	get_matrix_iso()
{
	const t_mat3x3 mat = {
		{
			{ 1.732051, -1.731977, 0.015941 },
			{ 1.000000, 0.981550, -2.009119 },
			{ 1.414214, 1.427169, 1.401138 }
		}
	};
	return (mat);
}
