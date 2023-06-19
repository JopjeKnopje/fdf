/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   view.c                                             :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/01 01:10:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 09:37:52 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void view_iso(t_projector *p)
{
	p->active_view.id_matrix = get_matrix_iso();
}


static void view_ortho(t_projector *p)
{
	(void) p;
}

static void view_saved(t_projector *p)
{
	ft_memcpy(&p->active_view, &p->saved_view, sizeof(t_view));

}

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
	void (*views[3])(t_projector *p) = {
		&view_ortho,
		&view_iso,
		&view_saved,
	};

	view_reset(&fdf->projector);
	fdf->projector.active_view.scalar = (float) fdf->image->width / (fdf->map->width * 2) * 0.58f;
	(*views[view])(&fdf->projector);
}
