/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyinput.c                                        :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:36:47 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 23:24:56 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "MLX42/MLX42_Input.h"
#include "fdf.h"
#include "timer.h"

static void	key_hook_rotate(t_fdf *fdf)
{
	t_view	*view;

	view = &fdf->projector.active_view;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		view_rotate(fdf, view, AXIS_X, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		view_rotate(fdf, view, AXIS_X, DIR_NEGATIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		view_rotate(fdf, view, AXIS_Y, DIR_NEGATIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		view_rotate(fdf, view, AXIS_Y, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		view_rotate(fdf, view, AXIS_Z, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		view_rotate(fdf, view, AXIS_Z, DIR_NEGATIVE);

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		view_move(fdf, view, AXIS_Y, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		view_move(fdf, view, AXIS_Y, DIR_NEGATIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		view_move(fdf, view, AXIS_X, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		view_move(fdf, view, AXIS_X, DIR_NEGATIVE);
}

static void 	key_hook_view(t_fdf	*fdf)
{
	t_view	*view;

	view = &fdf->projector.active_view;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		view_select(fdf, VIEW_ORTHO);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
		view_select(fdf, VIEW_ISO);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
	{
		if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_SHIFT))
			view_save(&fdf->projector);
		else
			view_select(fdf, VIEW_SAVED);
	}

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		view_scale(fdf, view, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		view_scale(fdf, view, DIR_NEGATIVE);

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_0))
		view_amplitude(fdf, view, DIR_POSTIVE);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_9))
		view_amplitude(fdf, view, DIR_NEGATIVE);
}

static void 	key_hook_misc(t_fdf	*fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_G))
	{
		if (timer_delta(fdf->timers[TIMER_VIEW_INPUT]) >= 0.2)
		{
			view_cylce_color_mode(fdf, DIR_POSTIVE);
			timer_start(fdf->timers[TIMER_VIEW_INPUT]);
		}
	}
}

void	key_hook(void *param)
{
	t_fdf *fdf;

	fdf = param;
	key_hook_rotate(fdf);
	key_hook_view(fdf);
	key_hook_misc(fdf);
}
