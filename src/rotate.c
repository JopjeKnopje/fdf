/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                          :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 16:29:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/01 01:28:13 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rotate(t_fdf *fdf, t_rotate_axis axis, t_rotate_dir dir)
{
	const t_mat3x3 (*matrices[3])(float angle) = {
		&get_matrix_rotate_x,
		&get_matrix_rotate_y,
		&get_matrix_rotate_z,
	};

	fdf->projector.id_matrix = mat3x3mul(fdf->projector.id_matrix, (*matrices[axis])(ANGLE_STEP * dir));
}
