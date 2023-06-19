/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   text.c                                             :+:    :+:            */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/18 19:07:46 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 12:51:22 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

void text_set(t_text_image *text, char *s)
{
	if (text->s)
		free(text->s);
	text->s = s;
}

void text_draw(mlx_t *mlx, t_text_image *text)
{
	if (text->drawn >= 100)
	{ 
		mlx_delete_image(mlx, text->image);
		text->drawn = 0;
	}
	else if (!text->drawn)
	{ 
		text->image = mlx_put_string(mlx, text->s, text->x, text->y);
		text->drawn = 0;
	}
	text->drawn++;

	// print_text(text);
}
