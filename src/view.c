/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   view.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/01 01:10:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/27 15:27:41 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static const char	*g_view_names[] = {\
	[VIEW_ORTHO] = "View: Orthographic",		\
	[VIEW_ISO] = "View: Isometric",				\
	[VIEW_SAVED] = "View: Saved",				\
};

static const char	*g_color_mode_names[] = {\
	[COLOR_MODE_MAP] = "Colormode: Map",		\
	[COLOR_MODE_HEIGHT] = "Colormode: Height",	\
};

static void	view_reset(t_projector *p)
{
	ft_bzero(&p->active_view.id_matrix, sizeof(t_mat3x3));
	p->active_view.id_matrix.data[0][0] = 1.00f;
	p->active_view.id_matrix.data[1][1] = 1.00f;
	p->active_view.id_matrix.data[2][2] = 1.00f;
	p->active_view.x_move = 0;
	p->active_view.y_move = 0;
	p->active_view.amplitude = .02;
	p->active_view.color_mode = COLOR_MODE_COUNT;
}

void	view_cylce_color_mode(t_fdf *fdf, t_direction dir)
{
	t_view	*v;
	char	*s;

	v = &fdf->projector.active_view;
	v->color_mode += dir;
	if (v->color_mode >= COLOR_MODE_COUNT)
		v->color_mode = 0;
	s = ft_strdup(g_color_mode_names[v->color_mode]);
	text_set(&fdf->ui.texts[TEXT_COLOR_MODE], s);
}

void	view_save(t_projector *p)
{
	ft_memcpy(&p->saved_view, &p->active_view, sizeof(t_view));
}

void	view_select(t_fdf *fdf, t_views view)
{
	const uint32_t	i_width = fdf->image->width;
	const uint32_t	m_width = fdf->map->width;
	t_view			*v;

	v = &fdf->projector.active_view;
	view_reset(&fdf->projector);
	v->scalar = (float)(i_width) / (m_width * 2) * 0.58f;
	if (view == VIEW_ISO)
		v->id_matrix = get_matrix_iso();
	else if (view == VIEW_SAVED)
		ft_memcpy(v, &fdf->projector.saved_view, sizeof(t_view));
	text_set(&fdf->ui.texts[TEXT_VIEW], ft_strdup(g_view_names[view]));
	ui_update_texts(fdf);
}
