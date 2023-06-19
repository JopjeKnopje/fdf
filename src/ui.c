/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:38:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 20:15:37 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "timer.h"
#include <math.h>
#include <stdio.h>

void	fps_hook(void *param)
{
	t_fdf	*fdf;
	char	*fps;
	static double time_old = 0;

	fdf = param;
	if (mlx_get_time() - time_old >= 1)
	{
		time_old = mlx_get_time();
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

static void setup_text(t_fdf *fdf)
{
	t_text_image	*t;
	uint32_t		i;

	i = 0;
	while (i < TEXT_COUNT)
	{
		t = &fdf->ui.texts[i];
		t->x = 25;
		t->y = 20 + (FONT_HEIGHT * i) + 10 * i;
		t->redraw = 1;
		if (i == TEXT_FPS)
			t->s = ft_strdup("FPS: 0");
		else if (i == TEXT_SCALAR)
			t->s = ft_strdup("Scalar: 0");
		else if (i == TEXT_AMPLITUDE)
			t->s = ft_strdup("Amplitude: 0");
		else if (i == TEXT_VIEW && !t->s)
			t->s = ft_strdup("View: 0");
		i++;
	}
}

void ui_init(t_fdf *fdf)
{
	t_view *view;

	view = &fdf->projector.active_view;
	setup_text(fdf);
	view_cylce_color_mode(fdf);
	view_scale(fdf, view, 0);
	view_move(fdf, view, 0, 0);
	view_amplitude(fdf, view, 0);
}

void ui_draw(t_fdf *fdf)
{
	draw_text_images(fdf);
}
