/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   graphics.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/20 01:22:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/22 16:52:39 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "MLX42/MLX42_Int.h"
#include "fdf.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>



void key_hook(void *param)
{
	t_fdf* fdf = param;

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->scalar++;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		fdf->scalar--;
}

void fps_hook(void *param)
{
	static int fps = 0;
	static double time_old = 0;
	if (mlx_get_time() - time_old >= 1)
	{
		time_old = mlx_get_time();
		printf("FPS: %d\n", fps);
		fps = 0;
	}
	else
		fps++;
}

void draw_clear(t_fdf *fdf)
{
	int x = 0;
	while (x < fdf->image->width)
	{
		int y = 0;
		while (y < fdf->image->height)
		{
			mlx_put_pixel(fdf->image, x, y, 0x000000FF);
			y++;
		}
		x++;
	
	}
}

void draw_points(t_fdf *fdf)
{
	t_node *tmp = fdf->map->points;
	uint32_t scalar = fdf->scalar;
	uint32_t x, y;

	while (tmp)
	{
		x = (tmp->point.x * scalar);
		y = (tmp->point.y * scalar);



		// https://clintbellanger.net/articles/isometric_math/
		// screen.x = (map.x - map.y) * TILE_WIDTH_HALF;
		// screen.y = (map.x + map.y) * TILE_HEIGHT_HALF;
		x = x * (scalar / 2) - y * (scalar / 2);
		y = y * (scalar / 2) + x * (scalar / 2);


		x += (fdf->image->width / 2) - (fdf->map->width * scalar / 2) + scalar;
		y += (fdf->image->height / 2) - (fdf->map->height * scalar / 2) + (scalar / 2);

		if (x >= 0 && x <= fdf->image->width && y >= 0 && y <= fdf->image->height)
			mlx_put_pixel(fdf->image, x, y, tmp->point.color);
		tmp = tmp->next;
	}
}


void draw_hook(void *param)
{
	t_fdf *fdf = param;
	draw_clear(fdf);
	draw_points(fdf);
}

int32_t graphics_init(t_fdf *fdf)
{

	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	if (!fdf->mlx)
	{
		error_print(mlx_strerror(mlx_errno));
		return (1);
	}

	fdf->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->scalar = 20;

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



	mlx_loop_hook(fdf->mlx, key_hook, fdf);
	mlx_loop_hook(fdf->mlx, fps_hook, fdf);
	mlx_loop_hook(fdf->mlx, draw_hook, fdf);

	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}
