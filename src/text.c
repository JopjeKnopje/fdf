/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   text.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/18 19:07:46 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 11:58:37 by jboeve        ########   odam.nl         */
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
	if (text->image)
	{
		mlx_delete_image(mlx, text->image);
	}
	text->image = mlx_put_string(mlx, text->s, text->x, text->y);
	// print_text(text);
}
