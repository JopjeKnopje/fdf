/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   projector.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/28 19:30:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/16 00:41:56 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fdf.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

static void scale(t_fdf *fdf, t_point *point)
{
	point->x *= fdf->projector.active_view.scalar;
	point->y *= fdf->projector.active_view.scalar;
	point->z *= fdf->projector.active_view.scalar;
}

static void offset(t_fdf *fdf, t_point *point)
{
	point->x -= ((float) fdf->map->width / 2) - 0.5;
	point->y -= ((float) fdf->map->height / 2) - 0.5;
}

static void center(t_fdf *fdf, t_point *point)
{
	point->x += ((float) fdf->image->width / 2) - fdf->projector.active_view.x_move;
	point->y += ((float) fdf->image->height / 2) - fdf->projector.active_view.y_move;
}

void projector_init(t_fdf *fdf)
{
	fdf->map->delta_z = map_find_delta_z(fdf);
	view_select(fdf, VIEW_ISO);
}

t_point projector(t_fdf *fdf, t_point point)
{
	t_point projected = point;

	offset(fdf, &projected);
	scale(fdf, &projected);

	projected.z *= fdf->projector.active_view.amplitude;
	projected = matmul(projected, fdf->projector.active_view.id_matrix);
	center(fdf, &projected);

	return (projected);
}
