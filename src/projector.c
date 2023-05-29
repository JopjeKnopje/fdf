/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   projector.c                                        :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/28 19:30:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/29 09:28:14 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fdf.h"
#include <math.h>
#include <stdio.h>

static void scale(t_fdf *fdf, t_point *point)
{
	point->x *= fdf->scalar;
	point->y *= fdf->scalar;
	point->z *= fdf->scalar;
}

static void center(t_fdf *fdf, t_point *point)
{
	point->x += (fdf->scalar / 2) + (fdf->image->width / 2) - (fdf->map->width * fdf->scalar / 2);
	point->y += (fdf->scalar / 2) + (fdf->image->height / 2) - (fdf->map->height * fdf->scalar / 2);
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


t_point projector(t_fdf *fdf, t_point point)
{
	t_point projected = point;

	int alpha = 35;
	int beta = 45;
	float angle = mlx_get_time() / 1;

	const float matrix_projection[3][3] = {
	//   x  y  z
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 0},
	};

	const float matrix_b[3][3] = {
		{cos(beta), 0, -sin(beta)},
		{0, 1, 0},
		{sin(beta), 0, cos(beta)},
	};

	const float matrix_a[3][3] = {
		{1, 0, 0},
		{0, cos(alpha), sin(alpha)},
		{0, -sin(alpha), cos(alpha)},
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




	printf("before | x: %d, y: %d, z: %d\n", projected.x, projected.y, projected.z);

	// center(fdf, &projected);
	// projected = matmul(projected, matrix_a);
	// projected = matmul(projected, matrix_b);
	// projected = matmul(projected, matrix_rotate_x);
	// projected = matmul(projected, matrix_rotate_z);
	// projected = matmul(projected, matrix_rotate_y);
	projected = matmul(projected, matrix_projection);
	scale(fdf, &projected);

	projected.x += fdf->image->width / 2;
	projected.y += fdf->image->height / 2;
	projected.z += fdf->image->width / 2;


	printf("after | x: %d, y: %d, z: %d\n", projected.x, projected.y, projected.z);

	return projected;

}
