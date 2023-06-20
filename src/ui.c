/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ui.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:38:19 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/20 17:34:30 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ui.h"

static void	setup_text(t_fdf *fdf)
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
		else if (i == TEXT_MAP_WIDTH)
			t->s = ft_strdup("Map width: 0");
		else if (i == TEXT_MAP_HEIGHT)
			t->s = ft_strdup("Map height: 0");
		i++;
	}
}

static void	setup_text_controls(t_fdf *fdf)
{
	t_text_image	*t;
	uint32_t		i;
	const uint32_t	offset = fdf->ui.texts[TEXT_COUNT - 1].y + FONT_HEIGHT;

	i = 0;
	while (i < CONTROL_TEXT_COUNT)
	{
		t = &fdf->ui.texts[i + TEXT_COUNT];
		t->x = 25;
		t->y = offset + (FONT_HEIGHT * 3) + (FONT_HEIGHT * i) + 10 * i;
		if (i >= CONTROL_TEXT_ROTATE_X)
			t->y += FONT_HEIGHT;
		text_set(t, ft_strdup(g_control_text_strings[i]));
		i++;
	}
}

void	ui_update_texts(t_fdf *fdf)
{
	t_view	*v;

	v = &fdf->projector.active_view;
	view_cylce_color_mode(fdf, 0);
	view_scale(fdf, v, 0);
	view_move(v, 0, 0);
	view_amplitude(fdf, v, 0);
}

void	ui_init(t_fdf *fdf)
{
	setup_text(fdf);
	setup_text_controls(fdf);
	text_set_num(&fdf->ui.texts[TEXT_MAP_WIDTH],
		"Map width: ", fdf->map->width);
	text_set_num(&fdf->ui.texts[TEXT_MAP_HEIGHT],
		"Map height: ", fdf->map->height);
}

void	ui_draw(t_fdf *fdf)
{
	uint32_t	i;

	i = 0;
	while (i < TEXT_COUNT + CONTROL_TEXT_COUNT)
	{
		text_draw(fdf->mlx, &(fdf->ui.texts[i]));
		i++;
	}
}
