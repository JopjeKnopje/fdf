/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   graphics.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/20 01:22:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/30 15:00:43 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Input.h"
#include "fdf.h"
#include "libft.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>


static void	hooks_init(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, key_hook, fdf);
	mlx_loop_hook(fdf->mlx, fps_hook, fdf);
	mlx_loop_hook(fdf->mlx, draw_hook, fdf);
}

int32_t	graphics_init(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
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
