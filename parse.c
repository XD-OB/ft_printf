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

int			is_valid(char *str)
{
	
}

void		check_fill(char *str, int pos,  t_list **head)
{
	int			i;
	t_list		*current;
	char		preflag[10];
	char		postflag[10];

	i = -1;
	if (!*str)
		error();
	while (++i < 10)
	{
		preflag[i] = '\0';
		postflag[i] = '\0';
	}
	current = *head;
	current = add_node(head);
	current->format.pos = pos;
	i = 0;
	while (is_preflag(*str))
	{
		preflag[i] = *str;
		i++;
		str++;
	}
	if (is_digit(str))
	{
		current->format.width = ft_atoi(str);
		while (is_digit(*str))
			str++;
	}
	if (*str == '.')
	{
		str++;
		if (is_digit(*str))
		{
			current->format.precis = ft_atoi(str);
			while (is_digit(*str))
				str++;
		}
	}
	while (is_postflag(*str))
	{
		postflag[i] = *str;
		i++;
		str++;		
	}
	if (is_format(*str))
	{
		current->format.convers = *str;
		current->format.flag = ft_strjoin(preflag, postflag, ft_strlen(preflag) + ft_strlen(postflag));
		if (!is_valid(current->format.flag))
		{
			free (current->format.flag);
			free (current);
			error();
		}
	}
	else
	{
		free (current->format.flag);
		free (current);
		error();
	}
}

t_list	*parse_format(char	*str)
{
	int		i;
	t_list	**lst;

	i = 0;
	*lst = NULL;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			check_fill(str, i - 1, lst);
		}
		str++;
		i++;
	}
	return (*lst);
}
