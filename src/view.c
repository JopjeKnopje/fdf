/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   view.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/01 01:10:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/04 00:32:27 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void view_iso(t_fdf *fdf)
{
	fdf->projector.active_view.id_matrix = mat3x3mul(fdf->projector.active_view.id_matrix, get_matrix_iso());
	fdf->projector.active_view.id_matrix = mat3x3mul(fdf->projector.active_view.id_matrix, get_matrix_rotate_x(1.58));
}


static void view_ortho(t_fdf *fdf)
{

}

static void view_saved(t_fdf *fdf)
{
	fdf->projector.active_view.x_move = fdf->projector.saved_view.x_move;
	fdf->projector.active_view.y_move = fdf->projector.saved_view.y_move;
	fdf->projector.active_view.scalar = fdf->projector.saved_view.scalar;
	fdf->projector.active_view.amplitude = fdf->projector.saved_view.amplitude;
	fdf->projector.active_view.id_matrix = mat3x3mul(fdf->projector.active_view.id_matrix, fdf->projector.saved_view.id_matrix);
}

static void view_reset(t_fdf *fdf)
{
	ft_bzero(&fdf->projector.active_view.id_matrix, sizeof(t_mat3x3));
	fdf->projector.active_view.id_matrix.data[0][0] = 1.00f;
	fdf->projector.active_view.id_matrix.data[1][1] = 1.00f;
	fdf->projector.active_view.id_matrix.data[2][2] = 1.00f;

	fdf->projector.active_view.x_move = 0;
	fdf->projector.active_view.y_move = 0;

	fdf->projector.active_view.scalar = 10;
	fdf->projector.active_view.amplitude = .02;
}

void view_select(t_fdf *fdf, t_views view)
{
	void (*views[3])(t_fdf *fdf) = {
		&view_ortho,
		&view_iso,
		&view_saved,
	};

	view_reset(fdf);
	(*views[view])(fdf);
}
