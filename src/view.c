/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   view.c                                             :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/01 01:10:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 09:57:45 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void view_reset(t_projector *p)
{
	ft_bzero(&p->active_view.id_matrix, sizeof(t_mat3x3));
	p->active_view.id_matrix.data[0][0] = 1.00f;
	p->active_view.id_matrix.data[1][1] = 1.00f;
	p->active_view.id_matrix.data[2][2] = 1.00f;
	p->active_view.x_move = 0;
	p->active_view.y_move = 0;
	p->active_view.amplitude = .02;
	p->active_view.color_mode = COLOR_MODE_MAP;
}

void view_select(t_fdf *fdf, t_views view)
{
	view_reset(&fdf->projector);
	fdf->projector.active_view.scalar = (float) fdf->image->width / (fdf->map->width * 2) * 0.58f;

	if (view == VIEW_ISO)
		fdf->projector.active_view.id_matrix = get_matrix_iso();
	else if (view == VIEW_SAVED)
		ft_memcpy(&fdf->projector.active_view, &fdf->projector.saved_view, sizeof(t_view));
}
