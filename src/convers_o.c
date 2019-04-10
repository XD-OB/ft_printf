/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_xxoub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:35:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/10 03:38:51 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		conv_o_1(t_lst *lst, t_chr **mychr, char c, int n)
{
	if (n == 0 && !lst->format->precis)
	{
		if (!ft_strchr(lst->format->flag, '#'))
		{
			(*mychr)->str = ft_strcnew(lst->format->width, ' ');
			((*mychr)->str)[lst->format->width] = '\0';
			(*mychr)->len = lst->format->width;
		}
		else
		{
			(!lst->format->width) ? lst->format->width++ : 0;
			c = (ft_strchr(lst->format->flag, '0')
					&& lst->format->precis == -1) ? '0' : ' ';
			(*mychr)->str = ft_strcnew(lst->format->width, c);
			((*mychr)->str)[lst->format->width] = '\0';
			if (ft_strchr(lst->format->flag, '-'))
				((*mychr)->str)[0] = '0';
			else
				((*mychr)->str)[lst->format->width - 1] = '0';
			(*mychr)->len = lst->format->width;
		}
		return (-1);
	}
	return (0);
}

static int		conv_o_2(t_lst *lst, char **nbr, char **str, int n)
{
	size_t		size;
	int			i;

	if (n && ft_strchr(lst->format->flag, '#'))
		flag_dash(nbr, 8);
	flag_apostrophe(nbr, lst->format);
	size = ft_max(ft_strlen(*nbr), lst->format->width);
	if (!(*str = ft_strnew(size)))
		return (-1);
	if (ft_strchr(lst->format->flag, '-'))
	{
		ft_strcpy(*str, *nbr);
		i = ft_strlen(*nbr);
		while (i < (int)size)
			(*str)[i++] = ' ';
	}
	else
	{
		i = 0;
		while (i < (int)(size - ft_strlen(*nbr) + 1))
			(*str)[i++] = ' ';
		ft_strcpy(&(*str)[--i], *nbr);
	}
	return (0);
}

void			conv_o_3(t_lst *lst, char **str, char *nbr)
{
	size_t		size;
	char		c;
	int			i;

	size = ft_strlen(nbr);
	c = (ft_strchr(lst->format->flag, '0')) ? '0' : ' ';
	if (lst->format->width > (int)size)
	{
		if (!ft_strchr(lst->format->flag, '-'))
		{
			i = lst->format->width - lst->format->precis - 1;
			while (++i < lst->format->width - (int)size)
				(*str)[i] = c;
		}
		else
		{
			i = (int)size - 1;
			while (++i < lst->format->precis)
				(*str)[i] = c;
		}
	}
}

int				conv_o_4(t_lst *lst, char **str, char *nbr, int n)
{
	if (conv_o_2(lst, &nbr, str, n) == -1)
		return (-1);
	if (!ft_strchr(lst->format->flag, '0') && lst->format->precis > 0
			&& lst->format->precis < lst->format->width)
		precis_o(str, lst->format, ft_strlen(nbr));
	else if (lst->format->precis >= lst->format->width)
		*str = all_zero_o(lst->format, nbr, lst->format->precis,
				(ft_strchr(lst->format->flag, '#')) ? 1 : 0);
	else if (ft_strchr(lst->format->flag, '0')
			&& lst->format->width > (int)ft_strlen(nbr)
			&& !ft_strchr(lst->format->flag, '-')
			&& lst->format->precis <= 0)
	{
		*str = all_zero_o(lst->format, nbr, lst->format->width,
				(ft_strchr(lst->format->flag, '#')) ? 1 : 0);
	}
	else
		conv_o_3(lst, str, nbr);
	free(nbr);
	return (0);
}

void			conv_o(t_lst *lst, t_chr **mychr, va_list ap)
{
	char		*str;
	char		*nbr;
	size_t		n;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format)
		: cast_xxoub(ap, lst->format);
	if (conv_o_1(lst, mychr, 0, n) == -1)
		return ;
	else
	{
		nbr = ft_utoa_base(n, 8);
		if (conv_o_4(lst, &str, nbr, n) == -1)
			return ;
		(*mychr)->str = str;
	}
	(*mychr)->len = ft_strlen(str);
}
