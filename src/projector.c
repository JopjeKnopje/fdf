/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   projector.c                                        :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/28 19:30:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/31 16:55:55 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fdf.h"
#include <math.h>
#include <stdio.h>



static void scale(t_fdf *fdf, t_point *point)
{
	point->x *= fdf->projector.scalar;
	point->y *= fdf->projector.scalar;
	point->z *= fdf->projector.scalar;
}

static void offset(t_fdf *fdf, t_point *point)
{
	point->x -= ((float) fdf->map->width / 2);
	point->y -= ((float) fdf->map->height / 2);
}

static void center(t_fdf *fdf, t_point *point)
{
	point->x += (fdf->projector.scalar / 2) + ((float) fdf->image->width / 2) - (fdf->projector.scalar / 2);
	point->y += (fdf->projector.scalar / 2) + ((float) fdf->image->height / 2) - (fdf->projector.scalar / 2);
}


// ex projector_rotate(ROTATE_Z_LEFT);
void project_rotate(t_fdf *fdf, t_rotate_axis rotate)
{
	// lookup table with function points that take rotate as argument.
}


void projector_init(t_fdf *fdf)
{
	fdf->projector.scalar = 60;
	fdf->projector.amplitude = .03;
	fdf->projector.angle_x = 0.82;
	fdf->projector.angle_y = -0.63;
	fdf->projector.angle_z = 0.48;

	fdf->projector.identity_matrix.data[0][0] = 1.0f;
	fdf->projector.identity_matrix.data[0][1] = 0.0f;
	fdf->projector.identity_matrix.data[0][2] = 0.0f;
	fdf->projector.identity_matrix.data[1][0] = 0.0f;
	fdf->projector.identity_matrix.data[1][1] = 1.0f;
	fdf->projector.identity_matrix.data[1][2] = 0.0f;
}

t_point projector(t_fdf *fdf, t_point point)
{
	t_point projected = point;


	offset(fdf, &projected);
	scale(fdf, &projected);

	projected.z *= fdf->projector.amplitude;
	projected = matmul(projected, fdf->projector.identity_matrix);
	// projected = matmul(projected, get_matrix_rotate_x(fdf->projector.angle_x));
	// projected = matmul(projected, get_matrix_rotate_y(fdf->projector.angle_y));
	// projected = matmul(projected, get_matrix_rotate_z(fdf->projector.angle_z));

	// projected = matmul(projected, get_matrix_ortho());
	// projected = matmul(projected, get_matrix_iso());
	center(fdf, &projected);


	return projected;
}
