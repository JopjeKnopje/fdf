/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   view.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/01 01:10:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/12 14:56:50 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void view_iso(t_projector *p)
{
	// TODO work out these values into one matrix
	p->active_view.id_matrix = mat3x3mul(p->active_view.id_matrix, get_matrix_iso());
	p->active_view.id_matrix = mat3x3mul(p->active_view.id_matrix, get_matrix_rotate_x(1.58));
}


static void view_ortho(t_projector *p)
{
	(void) p;
}

static void view_saved(t_projector *p)
{
	p->active_view.x_move = p->saved_view.x_move;
	p->active_view.y_move = p->saved_view.y_move;
	p->active_view.scalar = p->saved_view.scalar;
	p->active_view.amplitude = p->saved_view.amplitude;
	p->active_view.id_matrix = mat3x3mul(p->active_view.id_matrix, p->saved_view.id_matrix);
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
}

void view_select(t_fdf *fdf, t_views view)
{
	void (*views[3])(t_projector *p) = {
		&view_ortho,
		&view_iso,
		&view_saved,
	};

	view_reset(&fdf->projector);
	fdf->projector.active_view.scalar = (float) fdf->image->width / (fdf->map->width * 2) * 0.8f;
	(*views[view])(&fdf->projector);
}
