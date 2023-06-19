/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyinput.c                                        :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:36:47 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 17:37:40 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fdf.h"
#include "timer.h"
#include <math.h>
#include <stdio.h>

void	key_hook1(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		view_scale(&fdf->projector.active_view, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		view_scale(&fdf->projector.active_view, DIR_NEGATIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_0))
		view_amplitude(&fdf->projector.active_view, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_9))
		view_amplitude(&fdf->projector.active_view, DIR_NEGATIVE);

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		rotate(fdf, ROT_ANGLE_X, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		rotate(fdf, ROT_ANGLE_X, DIR_NEGATIVE);

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		rotate(fdf, ROT_ANGLE_Y, DIR_NEGATIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		rotate(fdf, ROT_ANGLE_Y, DIR_POSTIVE);
}

void 	key_hook2(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		rotate(fdf, ROT_ANGLE_Z, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		rotate(fdf, ROT_ANGLE_Z, DIR_NEGATIVE);

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		view_select(fdf, VIEW_ORTHO);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
		view_select(fdf, VIEW_ISO);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
	{
		if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_SHIFT))
			fdf->projector.saved_view = fdf->projector.active_view;
		else
			view_select(fdf, VIEW_SAVED);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
	{
		fdf->projector.active_view.y_move += fdf->projector.active_view.scalar;
		view_move(&fdf->projector.active_view, DIR_POSTIVE);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->projector.active_view.y_move -= fdf->projector.active_view.scalar;
}
void 	key_hook3(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->projector.active_view.x_move++;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->projector.active_view.x_move--;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_G))
	{
		if (timer_delta(fdf->timers[TIMER_VIEW_INPUT]) >= 0.2)
		{
			view_cylce_color_mode(fdf);
			timer_start(fdf->timers[TIMER_VIEW_INPUT]);
		}
	}
}
