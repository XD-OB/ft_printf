/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:43:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/03/05 19:51:21 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_format(char c)
{
	int		i;
	char	*ref;
	
	i = 0;
	ref = "cspdiouxXfegrkb}%";
	while (ref[i])
		if (c == ref[i++])
			return (1);
	return (0);
}

int		is_postflag(char c)
{
	int		i;
	char	*ref;
	
	i = 0;
	ref = "lLh$0+-r";
	while (ref[i])
		if (c == ref[i++])
			return (1);
	return (0);
}

int		is_preflag(char c)
{
	int	i;
	char	*ref;

	i = 0;
	ref = " 0+-#'*r";
	while (ref[i])
		if (c == ref[i++])
			return (1);
	return (0);
}

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

char            *cut_str(char *str, int p1, int p2)
{
        int     i;
        char    *ret;

        i = p1 - 1;
        if (!(ret = (char*)malloc(sizeof(char) * (p2 - p1 + 2))))
                return NULL;
        while (++i <= p2)
                ret[i - p1] = str[i];
        ret[i - p1] = '\0';
        return (ret);

}

void            init_chr(t_chr **chr)
{
        (*chr)->str = NULL;
        (*chr)->len = 0;
        (*chr)->next = NULL;
}

int	lstlen(t_lst *lst)
{
	int	size;
	t_lst	*curr;

	size = 0;
	curr = lst;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

void	free_lst(t_lst *lst)
{
	t_lst	*curr;

	curr = lst;
	while (curr)
	{
		lst = curr;
		free(curr->format->flag);
		free(curr->format);
		free(curr->arglist);
		curr = curr->next;
		free(lst);
	}
}

void	free_chr(t_chr *chr)
{
        t_chr   *tmp;

        while (chr)
        {
                tmp = chr;
                chr = chr->next;
                free (tmp);
        }
}

void	put_spstr(char *str)
{
	while (*str)
	{
		if (*str != '%')
			ft_putchar(*str);
		str++;
	}
}

void	print_lst(t_lst *lst)
{
	t_lst	*curr;

	curr = lst;
	while (curr)
	{
		ft_putstr("num argm: ");
		ft_putnbr(curr->format->argn);
		ft_putchar('\n');
		ft_putstr("position: ");
		ft_putnbr(curr->format->pos);
		ft_putchar('\n');
		ft_putstr("flags   : ");
		ft_putstr(curr->format->flag);
		ft_putchar('\n');
		ft_putstr("precision: ");
		ft_putnbr(curr->format->precis);
		ft_putchar('\n');
		ft_putstr("width    : ");
		ft_putnbr(curr->format->width);
		ft_putchar('\n');
		ft_putstr("conversion: ");
		ft_putchar(curr->format->convers);
		ft_putchar('\n');
		ft_putstr("\nNEXT_NODE\n\n");
		curr = curr->next;
	}
	ft_putstr("Size of list:\t");
	ft_putnbr(lstlen(lst));
	ft_putchar('\n');
}
