/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyinput.c                                        :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 19:36:47 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/29 23:01:04 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_hook(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->projector.scalar += 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		fdf->projector.scalar -= 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_0))
		fdf->projector.amplitude += 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_9))
		fdf->projector.amplitude -= 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->projector.angle += 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->projector.angle -= 0.1;
}
