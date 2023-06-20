/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   text.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/18 19:07:46 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/20 13:32:41 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	text_set_num(t_text_image *text, const char *s_base, int32_t n)
{
	char	*s;

	s = ft_itoa(n);
	text_set(text, ft_strjoin(s_base, s));
	free(s);
}

void	text_set(t_text_image *text, char *s)
{
	if (text->s)
	{
		free(text->s);
		text->s = NULL;
	}
	text->s = s;
	text->redraw = 1;
}

void	text_draw(mlx_t *mlx, t_text_image *text)
{
	if (!text->redraw)
		return ;
	if (text->image)
		mlx_delete_image(mlx, text->image);
	if (text->s)
	{
		text->image = mlx_put_string(mlx, text->s, text->x, text->y);
		text->redraw = 0;
	}
}
