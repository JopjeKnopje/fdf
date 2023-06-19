/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   graphics.c                                         :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/20 01:22:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 09:42:36 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "timer.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <MLX42/MLX42.h>
#include <math.h>



static void	resize(int32_t width, int32_t height, void* param)
{
	t_fdf *fdf = param;
	// TODO Error checking.
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

static uint8_t create_image(mlx_t *mlx, mlx_image_t **image, uint32_t width, uint32_t height)
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
	return 1;
}

static void timers_init(t_fdf *fdf)
{
	int i = 0;

	while (i < TIMER_COUNT) 
	{
		fdf->timers[i] = timer_init(mlx_get_time);
		i++;
	}
}

int32_t	graphics_init(t_fdf *fdf)
{
	fdf->mlx = mlx_init(DIM_WINDOW_WIDTH, DIM_WINDOW_HEIGHT, fdf->map->name, true);
	if (!fdf->mlx)
	{
		error_print(mlx_strerror(mlx_errno));
		return (1);
	}
	if (!create_image(fdf->mlx, &fdf->image, DIM_VIEWPORT_WIDTH, DIM_VIEWPORT_HEIGHT))
		return (1);
	if (!create_image(fdf->mlx, &fdf->ui.image, DIM_UI_WIDTH, DIM_UI_HEIGHT))
		return (1);
	hooks_init(fdf);
	timers_init(fdf);
	ui_init(fdf);
	projector_init(fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}
