/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                              :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:38:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/17 02:55:20 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void print_angles(void *param)
{
	t_fdf *fdf;

	fdf = param;
	const t_mat3x3 m = fdf->projector.active_view.id_matrix;

	float x = atan2(m.data[2][1], m.data[2][2]) * 180 / M_PI;
	float y = atan2(-m.data[2][0], sqrt(m.data[0][0] * m.data[0][0] + m.data[1][0] * m.data[1][0])) * 180 / M_PI;
	float z = atan2(m.data[1][0], m.data[0][0]) * 180 / M_PI;

	printf("x: %.3f°, y: %.3f°, z: %.3f°\n", x, y, z);
}


static void ui_draw_fps(t_fdf *fdf)
{
	char *s = "FPS: ";
	char *fps = ft_itoa(fdf->ui.fps);
	s = ft_strjoin(s, fps);
	if (fdf->ui.fps_image)
	{
		mlx_delete_image(fdf->mlx, fdf->ui.fps_image);
	}
	fdf->ui.fps_image = mlx_put_string(fdf->mlx, s, 20, 20);
	free(s);
	free(fps);
}

void	fps_hook(void *param)
{
	t_fdf *fdf;

	fdf = param;
	static double	time_old = 0;

	if (mlx_get_time() - time_old >= 1)
	{
		time_old = mlx_get_time();
		printf("FPS: %d\n", fdf->ui.fps);
		ui_draw_fps(fdf);
		fdf->ui.fps = 0;
	}
	else
		fdf->ui.fps++;
}



void ui_draw(t_fdf *fdf)
{
	;
}
