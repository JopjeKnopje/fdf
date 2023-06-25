/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                            :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:39:45 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/25 21:12:29 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ui.h"

static void	draw_clear(mlx_image_t *image, uint32_t c)
{
	const uint32_t	size = image->width * image->height;
	int				i;

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(image, i, 0, c);
		i++;
	}
}

void	fdf_put_pixel(t_fdf *fdf, t_point p)
{
	const uint32_t	width = fdf->image->width;
	const uint32_t	height = fdf->image->height;

	if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height)
		mlx_put_pixel(fdf->image, p.x, p.y, p.color.value);
}

void	draw_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	draw_clear(fdf->image, COLOR_BACKGROUND);
	draw_clear(fdf->ui.image, COLOR_BACKGROUND_UI);
	wireframe_draw(fdf);
	ui_draw(fdf);
}
