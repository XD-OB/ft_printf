#include "ft_printf.h"
#include <stdio.h>

int		check_fill(char *str, int pos,  t_lst *curr)
{
	int			i;
	char		preflag[6];
	char		postflag[6];

	i = -1;
	while (++i < 6)
	{
		preflag[i] = '\0';
		postflag[i] = '\0';
	}
	curr->format->pos = pos;
	i = 0;
	while (is_preflag(*str))
	{
		preflag[i++] = *str;
		str++;
	}
	if (ft_isdigit(*str))
	{
		curr->format->width = ft_atoi(str);
		while (ft_isdigit(*str))
			str++;
	}
	if (*str == '.')
	{
		if (ft_isdigit(*(++str)))
		{
			curr->format->precis = ft_atoi(str);
			while (ft_isdigit(*str))
				str++;
		}
	}
	i = 0;
	while (is_postflag(*str))
	{
		postflag[i++] = *str;
		str++;		
	}
	if (is_format(*str))
	{
		curr->format->convers = *str;
		curr->format->flag = ft_strjoin(preflag, postflag);
		if (!is_valid(curr->format->flag))
			return (-1);
	}
	else
		return (-1);
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
			if (!str[i + 1])
				frerrorlst(head);
			node = (t_lst*)malloc(sizeof(t_lst));
			node->format = (t_format*)malloc(sizeof(t_format));
			node->next = NULL;
			head = add_node(head, node);
			if (check_fill(&str[i + 1], i, node) == -1)
				frerrorlst(head);
			if (str[i + 1] == '%')
				i++;
			node = node->next;
		}
		i++;
	}
	return (head);
}
