/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   projector.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/28 19:30:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/30 15:00:39 by jboeve        ########   odam.nl         */
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

void projector_init(t_fdf *fdf)
{
	fdf->projector.scalar = 1;
	fdf->projector.amplitude = .03;
	fdf->projector.angle_x = 0.82;
	fdf->projector.angle_y = -0.63;
	fdf->projector.angle_z = 0.48;
}

t_point projector(t_fdf *fdf, t_point point)
{
	t_point projected = point;

	static double time_old = 0;


	offset(fdf, &projected);
	scale(fdf, &projected);


	if (mlx_get_time() - time_old >= 1)
	{
		printf("angle_x: %f | angle_y %f | angle_z %f\n", fdf->projector.angle_x, fdf->projector.angle_y, fdf->projector.angle_z);
		time_old = mlx_get_time();
	}

	projected.z *= fdf->projector.amplitude;
	projected = matmul(projected, get_matrix_rotate_x(fdf->projector.angle_x));
	projected = matmul(projected, get_matrix_rotate_y(fdf->projector.angle_y));
	projected = matmul(projected, get_matrix_rotate_z(fdf->projector.angle_z));
	// projected = matmul(projected, get_matrix_iso());
	projected = matmul(projected, get_matrix_ortho());
	center(fdf, &projected);


	return projected;

}
