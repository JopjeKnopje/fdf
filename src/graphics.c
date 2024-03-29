/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   graphics.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/20 01:22:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/27 15:52:35 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

static void	fps_hook(void *param)
{
	t_fdf			*fdf;

	fdf = param;
	if (timer_delta(fdf->fps_timer) >= 1)
	{
		text_set_num(&fdf->ui.texts[TEXT_FPS], "FPS: ", fdf->ui.fps);
		timer_start(fdf->fps_timer);
		fdf->ui.fps = 0;
	}
	else
		fdf->ui.fps++;
}

static void	resize(int32_t width, int32_t height, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	mlx_resize_image(fdf->image, width, height);
	if (width < DIM_UI_WIDTH)
		mlx_resize_image(fdf->ui.image, width, height);
	else
		mlx_resize_image(fdf->ui.image, DIM_UI_WIDTH, height);
}

static void	hooks_init(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, key_hook, fdf);
	mlx_loop_hook(fdf->mlx, fps_hook, fdf);
	mlx_loop_hook(fdf->mlx, draw_hook, fdf);
	mlx_resize_hook(fdf->mlx, resize, fdf);
}

static uint8_t	create_image(mlx_t *mlx, mlx_image_t **image,
		uint32_t width, uint32_t height)
{
	*image = mlx_new_image(mlx, width, height);
	if (!*image)
	{
		mlx_close_window(mlx);
		error_print(mlx_strerror(mlx_errno));
		return (0);
	}
	if (mlx_image_to_window(mlx, *image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		error_print(mlx_strerror(mlx_errno));
		return (0);
	}
	return (1);
}

int32_t	graphics_init(t_fdf *fdf)
{
	fdf->mlx = mlx_init(DIM_WINDOW_WIDTH, DIM_WINDOW_HEIGHT,
			fdf->map->name, true);
	if (!fdf->mlx)
	{
		error_print(mlx_strerror(mlx_errno));
		return (1);
	}
	if (!create_image(fdf->mlx, &fdf->image, DIM_VIEWPORT_WIDTH,
			DIM_VIEWPORT_HEIGHT))
		return (1);
	if (!create_image(fdf->mlx, &fdf->ui.image, DIM_UI_WIDTH,
			DIM_UI_HEIGHT))
		return (1);
	hooks_init(fdf);
	fdf->fps_timer = timer_init(&mlx_get_time);
	if (!fdf->fps_timer)
		return (1);
	ui_init(fdf);
	projector_init(fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}
