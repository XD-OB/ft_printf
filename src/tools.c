/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:43:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/10 00:31:17 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_lst		*add_node(t_lst *head, t_lst *node)
{
	t_lst	*current;

	current = head;
	if (!head)
		return (node);
	while (current->next)
		current = current->next;
	current->next = node;
	return (head);
}

void		init_chr(t_chr **chr)
{
	(*chr)->str = NULL;
	(*chr)->len = 0;
	(*chr)->next = NULL;
}

int			lstlen(t_lst *lst)
{
	t_lst	*curr;
	int		size;

	size = 0;
	curr = lst;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

void		free_lst(t_lst *lst)
{
	t_lst	*curr;

	curr = lst;
	while (curr)
	{
		lst = curr;
		free(curr->format->flag);
		free(curr->format);
		if (curr->arglist)
			free(curr->arglist);
		curr = curr->next;
		free(lst);
	}
}

void		free_chr(t_chr *chr)
{
	t_chr	*tmp;

	while (chr)
	{
		tmp = chr;
		chr = chr->next;
		free(tmp->str);
		free(tmp);
	}
}
