#include "ft_printf.h"

int		is_format(char c)
{
	int		i;
	char	*ref;
	
	i = 0;
	ref = "cspdiouxXfegrkb%";
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
	ref = "lLh$";
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
	ref = " 0+-#'*";
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

void	frerrorlst(t_lst *lst)
{
	t_lst	*curr;

	curr = lst;
	while (curr)
	{
		lst = curr;
		free (curr->format->flag);
		free (curr->format);
		curr = curr->next;
		free (lst);
	}
	error();
}

void	print_lst(t_lst *lst)
{
	t_lst	*curr;

	curr = lst;
	while (curr)
	{
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
