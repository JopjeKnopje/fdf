/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   graphics.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/20 01:22:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/01 02:40:13 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"
#include "fdf.h"
#include "libft.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>



static void	resize(int32_t width, int32_t height, void* param)
{
	t_fdf *fdf = param;
	mlx_resize_image(fdf->image, width, height);
}

static void	hooks_init(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, key_hook, fdf);
	mlx_loop_hook(fdf->mlx, fps_hook, fdf);
	mlx_loop_hook(fdf->mlx, draw_hook, fdf);
	mlx_loop_hook(fdf->mlx, print_angles, fdf);
	mlx_resize_hook(fdf->mlx, resize, fdf);
}

int32_t	graphics_init(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!fdf->mlx)
	{
		error_print(mlx_strerror(mlx_errno));
		return (1);
	}
	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->image)
	{
		mlx_close_window(fdf->mlx);
		error_print(mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
		mlx_close_window(fdf->mlx);
		error_print(mlx_strerror(mlx_errno));
		return (1);
	}
	hooks_init(fdf);
	projector_init(fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}
