/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 16:29:29 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/31 17:01:32 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


#define ANGLE_STEP 0.03

static void rotate_x(t_fdf *fdf, t_rotate_dir dir)
{
	fdf->projector.angle_x += ANGLE_STEP * dir;
	printf("rotate_x\n");
}

static void rotate_y(t_fdf *fdf, t_rotate_dir dir)
{
	printf("rotate_y\n");
}

static void rotate_z(t_fdf *fdf, t_rotate_dir dir)
{
	printf("rotate_z\n");
}

void (*rot_funcs[3])(t_fdf *fdf, t_rotate_dir dir) = {
	&rotate_x,
	&rotate_y,
	&rotate_z,
};

void rotate(t_fdf *fdf, t_rotate_axis axis, t_rotate_dir dir)
{
	(*rot_funcs[axis])(fdf, dir);
}
