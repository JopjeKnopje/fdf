/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:39:45 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/17 02:03:53 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

static void draw_clear(mlx_image_t *image, uint32_t c)
{
	const uint32_t size = image->width * image->height;
	int	i;

	i = 0;
	while (i < size)
	{
 		mlx_put_pixel(image, i, 0, c);
		i++;
	}
}

void fdf_put_pixel(t_fdf *fdf, t_point p)
{
	if (p.x >= 0 && p.x < fdf->image->width && p.y >= 0 && p.y < fdf->image->height)
		mlx_put_pixel(fdf->image, p.x, p.y, p.color.value);
}

void draw_hook(void *param)
{
	t_fdf *fdf = param;
	draw_clear(fdf->image, COLOR_BACKGROUND);
	draw_clear(fdf->ui_image, COLOR_BACKGROUND_UI);
	ui_draw(fdf);
	wireframe_draw(fdf);
}
