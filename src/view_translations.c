/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   view_translations.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/19 17:22:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/19 18:23:10 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void view_scale(t_view *view, t_direction dir)
{
	view->scalar += dir * (SCALAR_STEP * view->scalar / 2);
}


void view_amplitude(t_view *view, t_direction dir)
{
	view->amplitude += dir * (AMPLITUDE_STEP);
}

void view_move(t_view *view, t_axis axis, t_direction dir)
{
	if (axis == AXIS_X)
		view->x_move += dir * (view->scalar);
	else if (axis == AXIS_Y)
		view->y_move += dir * (view->scalar);
}

void view_rotate(t_view *view, t_axis axis, t_direction dir)
{
	const t_mat3x3 (*matrices[3])(float angle) = {
		&get_matrix_rotate_x,
		&get_matrix_rotate_y,
		&get_matrix_rotate_z,
	};
	view->id_matrix = mat3x3mul(view->id_matrix, (*matrices[axis])(ANGLE_STEP * dir));
}
