/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   free.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/20 00:29:45 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/27 15:42:19 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **s_split)
{
	int	i;

	i = 0;
	while (s_split[i])
	{
		free(s_split[i]);
		i++;
	}
	free(s_split);
}

void	free_lst(t_node *lst)
{
	t_node	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

static void	free_ui_texts(t_ui *ui)
{
	int	i;

	i = 0;
	while (i < TEXT_COUNT + CONTROL_TEXT_COUNT)
	{
		free(ui->texts[i].s);
		i++;
	}
}

void	free_fdf(t_fdf *fdf)
{
	free(fdf->map->points);
	free(fdf->map);
	timer_free(fdf->fps_timer);
	free_ui_texts(&fdf->ui);
}
