#include "ft_printf.h"

int		is_format(char c)
{
	int		i;
	char	*ref
	
	i = 0;
	ref = "cspdiouxXfegrkb%";
	while (ref[i])
		if (c == ref[i++])
			return (1);
	return (0);
}

int		is_postflag(char *str)
{
	int		i;
	char	*ref;
	
	i = 0;
	ref = "lLh$";
	if (ft_strstr(str, "hh") || ft_strstr(str, "ll"))
		return (1);
	while (ref[i])
		if (*str == ref[i++])
			return (1);
	return (0);
}

int		is_preflag(char c)
{
	int		i;
	char	*ref;

	i = 0;
	ref = " 0+-#'*";
	while (ref[i])
		if (c == ref[i++])
			return (1);
	return (0);
}

t_list	*add_node(t_list **head)
{
	t_list	*node;
	t_list	*tmp;
	
	tmp = *head;
	node = (t_list*)malloc(sizeof(t_list));
	node->next = NULL;
	while (tmp)
		tmp = tmp->next;
	tmp = node;
	return (node);
}

void	error()
{
	ft_putstr("Invalid format\n");
	exit(-1);
}

int		check_fill(char *str, t_list **head)
{
	t_list		*current;

	current = *head;
	if (!*str)
		return (-1);
	current = add_node(head);
	if 
}

void	parse_format(char	*str)
{
	t_list	**lst;

	*lst = NULL;
	while (*str)
	{
		if (*str == '%')
			if (check_fill(str + 1, lst) == -1)
				error();
		str++;
	}
}









