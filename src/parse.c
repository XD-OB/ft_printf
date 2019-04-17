/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:15:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 18:32:06 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			has_color(char *str)
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

char		*ft_strcolor(char *str)
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

int			check_fill(va_list tmp, char *str, int pos,
					t_lst *curr)
{
	char	*flag;
	char	*p;

	flag = ft_strnew(100);
	p = flag;
	curr->format->pos = pos;
	if (*str == '{')
	{
		str++;
		curr->format->flag = ft_strcolor(str);
		curr->format->convers = '}';
	}
	else
	{
		while (is_preflag(*str))
		{
			if (!ft_strchr(flag, *str))
			{
				*p = *str;
				if (*str == '$')
				{
					str++;
					curr->arglist = (va_list*)malloc(sizeof(va_list));
					va_copy(*(curr->arglist), tmp);
					curr->format->argn = ft_atoi(str);
					while (ft_isdigit(*str))
						str++;
					str--;
				}
				p++;
			}
			str++;
		}
		if (!*str)
		{
			free(flag);
			return (-1);
		}
		if (ft_isdigit(*str))
		{
			curr->format->width = ft_atoi(str);
			while (ft_isdigit(*str))
				str++;
		}
		if (!*str)
		{
			free(flag);
			return (-1);
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
		while (is_postflag(*str))
		{
			if ((*str == 'l' && !ft_strstr(flag, "ll"))
				|| !ft_strchr(flag, *str)
				|| (*str == 'h' && !ft_strstr(flag, "hh")))
			{
				*p = *str;
				p++;
			}
			str++;
		}
		if (!*str)
		{
			free(flag);
			return (-1);
		}
		curr->format->convers = *str;
		curr->format->flag = flag;
	}
	return (0);
}

void		init_node(t_lst *node)
{
	node->arglist = NULL;
	node->format->precis = -1;
	node->format->width = 0;
	node->format->convers = '\0';
	node->format->pos = 0;
	node->format->argn = 0;
}

t_lst		*parse_format(va_list ap, char *str, int *pflag)
{
	t_lst	*head;
	t_lst	*node;
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
			i++;
			if (check_fill(ap, &str[i], i - 1, node) != -1)
			{
				head = add_node(head, node);
				while (str[i] && str[i] != node->format->convers)
					i++;
			}
			else
			{
				*pflag = -1;
				free(node);
			}
			node = node->next;
		}
		i++;
	}
	return (head);
}
