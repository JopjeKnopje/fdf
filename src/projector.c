/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   projector.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/28 19:30:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/20 14:18:08 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	scale(t_fdf *fdf, t_point *point)
{
	point->x *= fdf->projector.active_view.scalar;
	point->y *= fdf->projector.active_view.scalar;
	point->z *= fdf->projector.active_view.scalar;
}

static void	offset(t_fdf *fdf, t_point *point)
{
	point->x -= ((float) fdf->map->width / 2) - 0.5;
	point->y -= ((float) fdf->map->height / 2) - 0.5;
}

static void	center(t_fdf *fdf, t_point *point)
{
	const t_view	*view = &fdf->projector.active_view;

	point->x += ((float) fdf->image->width / 2) - view->x_move
		+ ((float) fdf->ui.image->width / 2);
	point->y += ((float) fdf->image->height / 2) - view->y_move;
}

void	projector_init(t_fdf *fdf)
{
	view_select(fdf, VIEW_ISO);
}

t_point	projector(t_fdf *fdf, t_point point)
{
	t_point	projected;

	projected = point;
	projected.actual_z = point.z;
	offset(fdf, &projected);
	scale(fdf, &projected);
	projected.z *= fdf->projector.active_view.amplitude;
	projected = mat1x3mul(projected, fdf->projector.active_view.id_matrix);
	center(fdf, &projected);
	return (projected);
}
