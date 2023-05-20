/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   graphics.c                                        :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/20 01:22:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/20 02:05:33 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "MLX42/MLX42_Int.h"
#include "fdf.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>



// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void *param)
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

void fill_img(mlx_image_t *img, t_color c)
{
	int x = 0;
	while (x < img->width) 
	{
		int y = 0;
		while (y < img->height) 
		{
			mlx_put_pixel(img, x, y, c.c);
			y++;
		}
		x++;
	}
}

int32_t double_buffer_init(t_fdf *fdf)
{
	uint8_t i = 0;
	while (i < 2) 
	{
		fdf->buffers[i] = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		if (!fdf->buffers[i])
		{
			mlx_close_window(fdf->mlx);
			error_print(mlx_strerror(mlx_errno));
			return (1);
		}
		i++;
	}
	t_color c;


	c.c = 0xFF00FFFF;
	fill_img(fdf->buffers[0], c);
	c.c = 0xFFB00BFF;
	fill_img(fdf->buffers[1], c);

	fdf->image = fdf->buffers[0];


	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
		mlx_close_window(fdf->mlx);
		error_print(mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}

int32_t double_buffer_swap(t_fdf *fdf)
{
	fdf->image->enabled = false;
	if ((fdf->image) == (fdf->buffers[0]))
	{
		fdf->image = fdf->buffers[1];
		// printf("swapped buffer to 1\n");
	}
	else {
		fdf->image = fdf->buffers[0];
		// printf("swapped buffer to 0\n");
	}
	fdf->image->enabled = true;
	return (0);
}

void swap_hook(void *param)
{
	t_fdf* fdf = param;
	double_buffer_swap(fdf);
}


int32_t graphics_init(t_fdf *fdf)
{

	fdf->mlx = mlx_init(WIDTH, HEIGHT, TITLE, false);
	if (!fdf->mlx)
	{
		error_print(mlx_strerror(mlx_errno));
		return (1);
	}

	double_buffer_init(fdf);

	
	mlx_loop_hook(fdf->mlx, key_hook, fdf);
	mlx_loop_hook(fdf->mlx, fps_hook, fdf);
	mlx_loop_hook(fdf->mlx, swap_hook, fdf);
	// mlx_loop_hook(fdf->mlx, ft_randomize, fdf);

	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}
