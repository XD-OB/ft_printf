#include "ft_printf.h"
#include <stdio.h>

int	has_color(char *str)
{
	int	len;

	len = 0;
	while (str && *str != '}')
	{
		str++;
		len++;
	}
	if (!*str)
		return (0);
	return (len);
}

char	*ft_strcolor(char *str)
{
	char	*res;
	int		len;
	int		i;

	len = 0;
	while (str[len] && str[len] != '}' && str[len] != '%')
		len++;
	res = ft_strnew(len);
	i = -1;
	while (++i < len)
		res[i] = str[i];
	return (res);
}

int		check_fill(va_list tmp, char *str, int pos,  t_lst *curr)
{
	int		i;
	char		preflag[6];
	char		postflag[6];
	//char		color[7];

	i = -1;
	while (++i < 6)
	{
		preflag[i] = '\0';
		postflag[i] = '\0';
		//color[i] = '\0';
	}
	curr->format->pos = pos;
	i = 0;
	if (*str == '{')
	{
		str++;
		//if (has_color(str) <= 7 && has_color(str))
		//{
		//	while (*str != '}' && *str)
		//	{
		//		color[i] = *str;
		//		str++;
		//		i++;
		//	}
		//	color[i] = '\0';
		//}
		//curr->format->flag = ft_strdup(color);
		curr->format->flag = ft_strcolor(str);
		curr->format->convers = '}';
	}
	else
	{
		i = 0;
		while (is_preflag(*str))
		{
			preflag[i++] = *str;
			str++;
		}
		if (!*str)
		{
			free(curr);
			return -1;
		}
		if (ft_isdigit(*str))
		{
			curr->format->width = ft_atoi(str);
			while (ft_isdigit(*str))
				str++;
			if (*str == '$')
			{
				curr->arglist = (va_list*)malloc(sizeof(va_list));
				va_copy(*(curr->arglist), tmp);
				curr->format->argn = curr->format->width;
				curr->format->width = 0;
				str++;
			}
		}
		if (!*str)
		{
			free(curr);
			return -1;
		}
		if (*str == '.')
		{
			str++;
			if (*str == '*')
			{
				curr->format->precis = -2;
				str++;
			}
			else
				curr->format->precis = ft_atoi(str);
			while (ft_isdigit(*str))
				str++;
		}
		i = 0;
		while (is_postflag(*str))
		{
			postflag[i++] = *str;
			str++;		
		}
		if (!*str)
		{
			free(curr);
			return -1;
		}
		curr->format->convers = *str;
		curr->format->flag = ft_strjoin(preflag, postflag);
	}
	return (0);
}

void	init_node(t_lst *node)
{
	node->arglist = NULL;
	node->format->precis = -1;
	node->format->width = 0;
	node->format->convers = '\0';
	node->format->pos = 0;
	node->format->argn = 0;
}

t_lst	*parse_format(va_list ap, char	*str)
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
				return (head);
			node = (t_lst*)malloc(sizeof(t_lst));
			node->format = (t_format*)malloc(sizeof(t_format));
			init_node(node);
			node->next = NULL;
			if (check_fill(ap, &str[i + 1], i, node) != -1)
			{
				head = add_node(head, node);
				while (str[++i] != node->format->convers);
			}
			else
				free(node);
			node = node->next;
		}
		i++;
	}
	return (head);
}
