/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   list.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/19 23:59:15 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/27 15:22:24 by jboeve        ########   odam.nl         */
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

t_node	*lstadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!lst || !new)
		return (NULL);
	if (!(*lst))
		*lst = new;
	else
	{
		last = lstlast(*lst);
		last->next = new;
	}
	return (new);
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

t_node	*lstnew(t_point point)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->point = point;
	node->next = NULL;
	return (node);
}
