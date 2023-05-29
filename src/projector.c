/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   projector.c                                        :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/28 19:30:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/29 19:35:40 by joppe         ########   odam.nl         */
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

	point->x -= (fdf->map->width / 2);
	point->y -= (fdf->map->height / 2);
}

static void center(t_fdf *fdf, t_point *point)
{
	point->x += (fdf->projector.scalar / 2) + (fdf->image->width / 2) - (fdf->projector.scalar / 2);
	point->y += (fdf->projector.scalar / 2) + (fdf->image->height / 2) - (fdf->projector.scalar / 2);
}


t_point matmul(t_point point, const float matrix[3][3])
{
	float projx = point.x;
	float projy = point.y;
	float projz = point.z;

	point.x = (projx * matrix[0][0]) + (projy * matrix[0][1]) + (projz * matrix[0][2]);
	point.y = (projx * matrix[1][0]) + (projy * matrix[1][1]) + (projz * matrix[1][2]);
	point.z = (projx * matrix[2][0]) + (projy * matrix[2][1]) + (projz * matrix[2][2]);

	return (point);
}

void projector_init(t_fdf *fdf)
{
	fdf->projector.scalar = 15;
	fdf->projector.amplitude = .1;
	fdf->projector.angle = 1.6;
}


t_point projector(t_fdf *fdf, t_point point)
{
	t_point projected = point;

	float alpha = 0.61;
	float beta = 0.78;
	float angle = 1.6;

	const float matrix_ortho[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 0},
	};

	
	const float matrix_a[3][3] = {
		{sqrt(3), 0, -sqrt(3)},
		{1, 2, 1},
		{sqrt(2), -sqrt(2), sqrt(2)},
	};

	const float matrix_b[3][3] = {
		{1, 0, 0},
		{0, cos(angle), -sin(angle)},
		{0, sin(angle), cos(angle)},
	};

	const float matrix_rotate_x[3][3] = {
		{1, 0, 0},
		{0, cos(angle), -sin(angle)},
		{0, sin(angle), cos(angle)},
	};

	const float matrix_rotate_y[3][3] = {
		{cos(angle), 0, sin(angle)},
		{0, 1, 0},
		{-sin(angle), 0, cos(angle)},
	};

	const float matrix_rotate_z[3][3] = {
		{cos(angle), -sin(angle), 0},
		{sin(angle), cos(angle), 0},
		{0, 0, 1},
	};

	offset(fdf, &projected);
	scale(fdf, &projected);
	projected.z *= fdf->projector.amplitude;

	// projected = matmul(projected, matrix_rotate_x);
	// projected = matmul(projected, matrix_rotate_z);
	// projected = matmul(projected, matrix_rotate_y);

	projected = matmul(projected, matrix_rotate_x);
	projected = matmul(projected, matrix_a);
	projected = matmul(projected, matrix_ortho);
	center(fdf, &projected);


	return projected;

}
