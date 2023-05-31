/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                          :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 16:29:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/01 00:17:45 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <unistd.h>


#define ANGLE_STEP 0.03

static void rotate_x(t_fdf *fdf, t_rotate_dir dir)
{
	fdf->projector.identity_matrix = mat3x3mul(fdf->projector.identity_matrix, get_matrix_rotate_x(0.01f * dir));
}

static void rotate_y(t_fdf *fdf, t_rotate_dir dir)
{
	fdf->projector.identity_matrix = mat3x3mul(fdf->projector.identity_matrix, get_matrix_rotate_y(0.01f * dir));
}

static void rotate_z(t_fdf *fdf, t_rotate_dir dir)
{
	fdf->projector.identity_matrix = mat3x3mul(fdf->projector.identity_matrix, get_matrix_rotate_z(0.01f * dir));
}

void (*rot_funcs[3])(t_fdf *fdf, t_rotate_dir dir) = {
	&rotate_x,
	&rotate_y,
	&rotate_z,
};

void rotate(t_fdf *fdf, t_rotate_axis axis, t_rotate_dir dir)
{
	(*rot_funcs[axis])(fdf, dir);
}
