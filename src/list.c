/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   list.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/19 23:59:15 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/20 00:04:43 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	lstsize(t_node *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	lstadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = lstlast(*lst);
		last->next = new;
	}
}

t_node	*lstlast(t_node *lst)
{
	t_node	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_node	*lstnew(void *point)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->point = point;
	node->next = NULL;
	return (node);
}

void	lstclear(t_node **lst, void (*del)(void*))
{
	t_node	*tmp;
	t_node	*old;

	tmp = *lst;
	while (tmp)
	{
		old = tmp;
		del(tmp->point);
		tmp = tmp->next;
		free(old);
	}
	*lst = NULL;
}
