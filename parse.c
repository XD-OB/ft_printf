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
	int		i;
	char	*ref;

	i = 0;
	ref = " 0+-#'*";
	while (ref[i])
		if (c == ref[i++])
			return (1);
	return (0);
}

void	add_node(t_lst *head)
{
	t_lst	*node;
	
	node = (t_lst*)malloc(sizeof(t_lst));
	while (head)
		head = head->next;
	head = node;
	head->next = NULL;
}

void	error()
{
	ft_putstr("Invalid format\n");
	exit(-1);
}

int			is_valid(char *str)
{
	return (1);	
}

void		check_fill(char *str, int pos,  t_lst **head)
{
	int			i;
	t_lst		*current;
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
	/*add_node(*head);
	current = *head;
	while (current->next)
		current = current->next;
	current->format->pos = pos;
	i = 0;
	while (is_preflag(*str))
	{
		preflag[i] = *str;
		i++;
		str++;
	}
	if (ft_isdigit(*str))
	{
		current->format->width = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
	}
	if (*str == '.')
	{
		str++;
		if (ft_isdigit(*str))
		{
			current->format->precis = ft_atoi(str);
			while (ft_isdigit(*str))
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
		current->format->convers = *str;
		current->format->flag = ft_strjoin(preflag, postflag);
		if (!is_valid(current->format->flag))
		{
			free (current->format->flag);
			free (current);
			error();
		}
	}
	else
	{
		free (current->format->flag);
		free (current);
		error();
	}*/
}

void	parse_format(char	*str, t_lst **lst)
{
	int		i;

	i = 0;
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
}
