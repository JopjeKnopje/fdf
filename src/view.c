/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   view.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/01 01:10:34 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/01 01:49:10 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void view_iso(t_fdf *fdf)
{
	ft_bzero(&fdf->projector.id_matrix, sizeof(t_mat3x3));
	fdf->projector.id_matrix.data[0][0] = 1.00f;
	fdf->projector.id_matrix.data[1][1] = 1.00f;
	fdf->projector.id_matrix.data[2][2] = 1.00f;

	fdf->projector.id_matrix = mat3x3mul(fdf->projector.id_matrix, get_matrix_iso());
	fdf->projector.id_matrix = mat3x3mul(fdf->projector.id_matrix, get_matrix_rotate_x(1.58));
}


static void view_ortho(t_fdf *fdf)
{
	ft_bzero(&fdf->projector.id_matrix, sizeof(t_mat3x3));
	fdf->projector.id_matrix.data[0][0] = 1.00f;
	fdf->projector.id_matrix.data[1][1] = 1.00f;
	fdf->projector.id_matrix.data[2][2] = 1.00f;
}

static void view_load(t_fdf *fdf)
{
	ft_bzero(&fdf->projector.id_matrix, sizeof(t_mat3x3));
	fdf->projector.id_matrix.data[0][0] = 1.00f;
	fdf->projector.id_matrix.data[1][1] = 1.00f;
	fdf->projector.id_matrix.data[2][2] = 1.00f;

	fdf->projector.id_matrix = mat3x3mul(fdf->projector.id_matrix, fdf->projector.saved_view);
}

void view_select(t_fdf *fdf, t_view view)
{
	void (*views[3])(t_fdf *fdf) = {
		&view_ortho,
		&view_iso,
		&view_load,
	};

	(*views[view])(fdf);
}
