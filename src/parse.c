#include "ft_printf.h"
#include <stdio.h>

int	take_color(char *str)
{
	int	i;
	//char	color[7];

	i = 0;
	while (str && *str != '}')
	{
	//	color[i] = *str;
		str++;
		i++;
	}
	//color[i] = '\0';
	if (!*str)
		return (0);
	/*
	if (!ft_strcmp(color, "red"))
		return (ft_strdup("red"));
	if (!ft_strcmp(color, "green"))
		return (ft_strdup("green"));
	if (!ft_strcmp(color, "blue"))
		return (ft_strdup("blue"));
	if (!ft_strcmp(color, "purple"))
		return (ft_strdup("purple"));
	if (!ft_strcmp(color, "yellow"))
		return (ft_strdup("yellow"));
	if (!ft_strcmp(color, "cyan"))
		return (ft_strdup("cyan"));
	if (!ft_strcmp(color, "eoc"))
		return (ft_strdup("eoc"));
	return NULL;*/
	return (1);
}

int		check_fill(char *str, int pos,  t_lst *curr)
{
	//int			o;
	int			i;
	char		preflag[6];
	char		postflag[6];
	char		color[7];

	//o = 0;
	i = -1;
	while (++i < 6)
	{
		preflag[i] = '\0';
		postflag[i] = '\0';
		color[i] = '\0';
	}
	curr->format->pos = pos;
	i = 0;
	if (*str == '{')
	{
		str++;
		if (take_color(str))
		{
			while (*str != '}' && *str)
			{
				color[i] = *str;
				str++;
				i++;
			}
			color[i] = '\0';
		}
		curr->format->flag = ft_strdup(color);
		curr->format->convers = '}';
	}
	else
	{
		i = -1;
		while (++i < 6)
		{
			preflag[i] = '\0';
			postflag[i] = '\0';
			color[i] = '\0';
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
			str++;
			//if (!(curr->format->precis = ft_atoi(str)))
			//	o = 1;
			curr->format->precis = ft_atoi(str);
			while (ft_isdigit(*str))
				str++;
			//}
		}
		i = 0;
		while (is_postflag(*str))
		{
			postflag[i++] = *str;
			str++;		
		}
		curr->format->convers = *str;
		//if (*str == 'd' && o == 1)
		//	curr->format->precis = -2;
		curr->format->flag = ft_strjoin(preflag, postflag);
	}
	//if (!is_valid(curr->format->flag))
		//return (-1);
	return (0);
}

void	init_node(t_lst *node)
{
	node->format->precis = -1;
	node->format->width = 0;
	node->format->convers = '\0';
	//node->format->flag = ft_strnew(0);
	node->format->pos = 0;

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
			{
				free_lst(head);
				exit(-1);
			}
			node = (t_lst*)malloc(sizeof(t_lst));
			node->format = (t_format*)malloc(sizeof(t_format));
			init_node(node);
			node->next = NULL;
			if (check_fill(&str[i + 1], i, node) != -1)
				head = add_node(head, node);
			else
				free(node);
			if (str[i + 1] == '%')
				i++;
			if (check_fill(&str[i + 1], i, node) != -1)
				node = node->next;
		}
		i++;
	}
	return (head);
}
