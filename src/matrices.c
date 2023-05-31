/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   matrices.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/30 12:02:30 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/01 01:04:08 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_mat3x3	get_matrix_rotate_x(float angle)
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

t_mat3x3	get_matrix_rotate_y(float angle)
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

t_mat3x3	get_matrix_rotate_z(float angle)
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

t_mat3x3	get_matrix_ortho()
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

t_mat3x3	get_matrix_iso()
{
	const t_mat3x3 mat = {
		{
			{sqrt(3), 0, -sqrt(3)},
			{1, 2, 1},
			{sqrt(2), -sqrt(2), sqrt(2)},
		}
	};
	return (mat);
}
