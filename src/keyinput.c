/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyinput.c                                        :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:36:47 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/01 02:02:53 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fdf.h"
#include <stdio.h>

void	key_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->projector.scalar += SCALAR_STEP;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		fdf->projector.scalar -= SCALAR_STEP;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_0))
		fdf->projector.amplitude += AMPLITUDE_STEP;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_9))
		fdf->projector.amplitude -= AMPLITUDE_STEP;

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		rotate(fdf, ROT_ANGLE_X, ROT_DIR_POS);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		rotate(fdf, ROT_ANGLE_X, ROT_DIR_NEG);

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		rotate(fdf, ROT_ANGLE_Y, ROT_DIR_NEG);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		rotate(fdf, ROT_ANGLE_Y, ROT_DIR_POS);

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		rotate(fdf, ROT_ANGLE_Z, ROT_DIR_POS);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		rotate(fdf, ROT_ANGLE_Z, ROT_DIR_NEG);

	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		view_select(fdf, VIEW_ORTHO);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
		view_select(fdf, VIEW_ISO);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
	{
		if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT_SHIFT))
			fdf->projector.saved_view = fdf->projector.id_matrix;
		else
			view_select(fdf, VIEW_SAVED);
	}

}
