/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   graphics.c                                         :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/20 01:22:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/29 09:36:23 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "MLX42/MLX42_Input.h"
#include "MLX42/MLX42_Int.h"
#include "fdf.h"
#include "libft.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>

static void key_hook(void *param)
{
	t_fdf* fdf = param;

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->scalar++;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		fdf->scalar--;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_0))
		fdf->amplitude++;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_9))
		fdf->amplitude--;
}

static void fps_hook(void *param)
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

static void draw_clear(t_fdf *fdf)
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

static t_point map_to_iso(t_point point, uint32_t scalar, uint32_t width, uint32_t amplitude)
{
	t_point point_iso;

	ft_bzero(&point_iso, sizeof(t_point));

	// x1 = (x - y) * cos(0.8);
	// y1 = (x + y) * sin (0.61) - z;

	point_iso.x = ((point.x - point.y + width - 1) * scalar) * cos(0.8);
	point_iso.y = ((point.x + point.y) * scalar / 2) * (sin(0.61)) - (point.z + scalar);
	point_iso.y += 100;
	// printf("x: %d | y: %d\n", point_iso.x, point_iso.y);


	// point_iso.x = (point.x - point.y) * scalar;
	// point_iso.x += (width - 1) * scalar;
	// point_iso.y = (point.x + point.y) * (scalar / 2);

	point_iso.z = point.z;
	point_iso.color = point.color;

	return (point_iso);
}

void fdf_put_pixel(t_fdf *fdf, t_point p)
{
	if (p.x >= 0 && p.x <= fdf->image->width && p.y >= 0 && p.y <= fdf->image->height)
		mlx_put_pixel(fdf->image, p.x, p.y, p.color);
	// else
	//  printf("fdf_put_pixel: out of bounds\n");
}


static void draw_lines(t_fdf *fdf, uint32_t x, uint32_t y)
{
	t_point projected;
	projected = projector(fdf, fdf->map->points[y * fdf->map->width + x]);
	fdf_put_pixel(fdf, projected);
}

static void draw_wireframe(t_fdf *fdf)
{

	t_point projected1;
	projected1 = projector(fdf, fdf->map->points[1 * fdf->map->width + 0]);
	fdf_put_pixel(fdf, projected1);

	t_point projected2;
	projected2 = projector(fdf, fdf->map->points[4 * fdf->map->width + 9]);
	fdf_put_pixel(fdf, projected2);

	t_point projected3;
	projected3 = projector(fdf, fdf->map->points[4 * fdf->map->width + 9]);
	fdf_put_pixel(fdf, projected3);

	line_draw(fdf, projected1, projected2);
	line_draw(fdf, projected3, projected2);
	

	// uint32_t x;
	// uint32_t y;
	//
	// x = 0;
	// while (x < fdf->map->width)
	// {
	// 	y = 0;
	// 	while (y < fdf->map->height)
	// 	{
	// 		draw_lines(fdf, x, y);
	// 		y++;
	// 	}
	// 	x++;
	// }
}


static void draw_hook(void *param)
{
	t_fdf *fdf = param;
	draw_clear(fdf);
	draw_wireframe(fdf);
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
	fdf->scalar = 5;
	fdf->amplitude = 1;

	mlx_loop_hook(fdf->mlx, key_hook, fdf);
	mlx_loop_hook(fdf->mlx, fps_hook, fdf);
	mlx_loop_hook(fdf->mlx, draw_hook, fdf);

	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (EXIT_SUCCESS);
}
