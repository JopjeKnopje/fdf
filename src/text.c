/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   text.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/18 19:07:46 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 23:42:32 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdint.h>
#include <stdio.h>

void text_set(t_text_image *text, char *s)
{
	if (text->s)
	{ 
		free(text->s);
		text->s = NULL;
	}
	text->s = s;
	text->redraw = 1;
}

void text_draw(mlx_t *mlx, t_text_image *text)
{
	if (!text->redraw)
		return ;	
	if (text->image)
	{ 
		mlx_delete_image(mlx, text->image);
	}
	if (text->s)
	{ 
		text->image = mlx_put_string(mlx, text->s, text->x, text->y);
		text->redraw = 0;
	}
}
