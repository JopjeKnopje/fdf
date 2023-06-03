/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                          :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 16:29:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/04 00:22:48 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>

void rotate(t_fdf *fdf, t_rotate_axis axis, t_rotate_dir dir)
{
	const t_mat3x3 (*matrices[3])(float angle) = {
		&get_matrix_rotate_x,
		&get_matrix_rotate_y,
		&get_matrix_rotate_z,
	};

	fdf->projector.active_view.id_matrix = mat3x3mul(fdf->projector.active_view.id_matrix, (*matrices[axis])(ANGLE_STEP * dir));
}
