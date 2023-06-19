/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                              :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:38:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 11:09:35 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>

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

void	fps_hook(void *param)
{
	t_fdf	*fdf;
	char	*fps;
	static double time_old = 0;

	fdf = param;
	if (mlx_get_time() - time_old >= 1)
	{
		time_old = mlx_get_time();
		// printf("FPS: %d\n", fdf->ui.fps);

		fps = ft_itoa(fdf->ui.fps);
		text_set(&fdf->ui.texts[TEXT_FPS], ft_strjoin("FPS: ", fps));
		free(fps);
		fdf->ui.fps = 0;
	}
	else
		fdf->ui.fps++;
}

static	void draw_text_images(t_fdf *fdf)
{
	uint32_t	i;

	i = 0;
	while (i < TEXT_COUNT)
	{
		text_draw(fdf->mlx, &(fdf->ui.texts[i]));
		i++;
	}
}


void ui_init(t_fdf *fdf)
{
	t_text_image	*t;
	uint32_t		i;

	i = 0;
	while (i < TEXT_COUNT)
	{
		t = &fdf->ui.texts[i];
		t->x = 20;
		t->y = 20 + (FONT_HEIGHT * i) + 20 * i;
		if (i == TEXT_FPS)
			t->s = ft_strdup("FPS: 0");
		else if (i == TEXT_SCALAR)
			t->s = ft_strdup("Scalar: 123");
		else if (i == TEXT_AMPLITUDE)
			t->s = ft_strdup("Amplitude: 123");
		else if (i == TEXT_VIEW)
			t->s = ft_strdup("View: 123");
		i++;
	}
}

void ui_draw(t_fdf *fdf)
{
	draw_text_images(fdf);
}
