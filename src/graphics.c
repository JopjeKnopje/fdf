/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   graphics.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/20 01:22:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/20 03:02:20 by joppe         ########   odam.nl         */
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



void key_hook(void *param)
{
	t_fdf* fdf = param;

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
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

	uint32_t scalar = 50;

	int x, y;
	while (tmp)
	{
		// canvasWidth/2 - rectangleWidth/2
		x = (tmp->point.x * scalar);
		y = (tmp->point.y * scalar);

		x += (WIDTH / 2) - (fdf->map->width * scalar / 2) + scalar / 2;
		y += (HEIGHT / 2) - (fdf->map->height * scalar / 2) + scalar / 2;

		mlx_put_pixel(fdf->image, x, y, COLOR_POINT);
		tmp = tmp->next;
	}
}


void draw_hook(void *param)
{
	t_fdf *fdf = param;
	// ft_randomize(param);
	draw_clear(fdf);
	draw_points(fdf);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	t_fdf *fdf = param;
	for (int32_t i = 0; i < fdf->image->width; ++i)
	{
		for (int32_t y = 0; y < fdf->image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(fdf->image, i, y, color);
		}
	}
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