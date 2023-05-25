/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/22 22:11:03 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/25 22:28:25 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdint.h>


void line_draw(t_fdf *fdf, t_point p_start, t_point p_end)
{
	t_point tmp;
	int32_t x_start = p_start.x;
	int32_t y_start = p_start.y;
	int32_t x_end = p_end.x;
	int32_t y_end = p_end.y;

	int32_t dx = abs(x_end - x_start);
	int32_t dy = abs(y_end - y_start);

	int32_t pk = 2 * (dy - dx);

	int32_t i = 0;
	while (i <= dx)
	{
		if (x_start < x_end)
			x_start++;
		else
			x_start--;
		if (pk < 0)
		{
			if (dx > dy)
			{
				tmp.x = x_start;
				tmp.y = y_start;
				fdf_put_pixel(fdf, tmp);
				pk = pk + 2 * dy;
			}
			else 
			{
				tmp.x = x_start;
				tmp.y = y_start;
				fdf_put_pixel(fdf, tmp);
				pk = pk + 2 * dy;
			}
		}
		else
		{
			if (y_start < y_end)
				y_start++;
			else
				y_start--;
			if (dx > dy)
			{
				tmp.x = x_start;
				tmp.y = y_start;
				fdf_put_pixel(fdf, tmp);
			}
			else 
			{
				tmp.x = x_start;
				tmp.y = y_start;
				fdf_put_pixel(fdf, tmp);
			}
			pk = pk + 2 * dy - 2 * dx;
		}
		i++;
	}
}
