/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   view_translations.c                                :+:    :+:            */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/19 17:22:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/20 17:33:03 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void view_scale(t_fdf *fdf, t_view *view, t_direction dir)
{
	view->scalar += dir * (SCALAR_STEP * view->scalar / 2);
	text_set_num(&fdf->ui.texts[TEXT_SCALAR], "Scalar: ", view->scalar);
}

void view_amplitude(t_fdf *fdf, t_view *view, t_direction dir)
{
	view->amplitude += dir * (AMPLITUDE_STEP);
	text_set_num(&fdf->ui.texts[TEXT_AMPLITUDE], "Amplitude: ", view->amplitude * 100);
}

void			view_move(t_view *view, t_axis axis, t_direction dir)
{
	if (axis == AXIS_X)
		view->x_move += dir * (view->scalar / 3);
	else if (axis == AXIS_Y)
		view->y_move += dir * (view->scalar / 3);
}

void view_rotate(t_view *view, t_axis axis, t_direction dir)
{
	t_mat3x3 (*matrices[3])(float angle) = {
		&get_matrix_rotate_x,
		&get_matrix_rotate_y,
		&get_matrix_rotate_z,
	};
	view->id_matrix = mat3x3mul(view->id_matrix, (*matrices[axis])(ANGLE_STEP * dir));
}
