/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                              :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:38:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/01 02:52:19 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void print_angles(void *param)
{
	t_fdf *fdf;

	fdf = param;
	const t_mat3x3 m = fdf->projector.id_matrix;

	float x = atan2(m.data[2][1], m.data[2][2]) * 180 / M_PI;
	float y = atan2(-m.data[2][0], sqrt(m.data[0][0] * m.data[0][0] + m.data[1][0] * m.data[1][0])) * 180 / M_PI;
	float z = atan2(m.data[1][0], m.data[0][0]) * 180 / M_PI;

	printf("x: %.3f°, y: %.3f°, z: %.3f°\n", x, y, z);
}

void	fps_hook(void *param)
{
	static int		fps = 0;
	static double	time_old = 0;

	if (mlx_get_time() - time_old >= 1)
	{
		time_old = mlx_get_time();
		printf("FPS: %d\n", fps);
		fps = 0;
	}
	else
		fps++;
}

