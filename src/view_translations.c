/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   view_translations.c                               :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/19 17:22:23 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/19 17:30:38 by jboeve        ########   odam.nl         */
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

void view_move(t_view *view, t_direction dir)
{

}

void view_rotate(t_view *view, t_rotate_axis axis, t_direction dir)
{

}
