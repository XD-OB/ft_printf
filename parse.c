#include "ft_printf.h"

void		check_fill(char *str, int pos,  t_lst *current)
{
	int			i;
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
	i = 0;
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
	}
}

t_lst	*parse_format(char	*str)
{
	t_lst		*head;
	t_lst		*node;
	int		i;

	i = 0;
	head = NULL;
	while (str[i])
	{
		if (str[i] == '%')
		{
			node = (t_lst*)malloc(sizeof(t_lst));
			node->format = (t_format*)malloc(sizeof(t_format));
			node->next = NULL;
			head = add_node(head, node);
			check_fill(&str[i], i++, node);
			node = node->next;
		}
		i++;
	}
	return (head);
}
