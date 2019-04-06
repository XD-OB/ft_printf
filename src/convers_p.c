/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:12:58 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/05 15:39:05 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*all_zero_p(char *nbr, int precis, int width)
{
	char		*res;
	int			len;
	int			len_nbr;
	int			i;
	int			j;

	len_nbr = (int)ft_strlen(nbr) - 2;
	len = precis;
	if (!width)
		len += 2;
	res = ft_strnew(len);
	i = 0;
	j = 2;
	res[i++] = '0';
	res[i++] = 'X';
	while (i < (len - len_nbr))
		res[i++] = '0';
	while (i < len)
		res[i++] = nbr[j++];
	return (res);
}

/*
**	i:		i[0]: i			i[1]: j
*/

static void		precis_p(char **str, t_format *fmt, size_t nbr_len)
{
	int			i[2];
	int			len;
	char		*nbr;

	len = nbr_len - 2;
	if (ft_strchr(fmt->flag, '-'))
	{
		i[0] = 0;
		i[1] = 2;
		nbr = ft_strdup(*str);
		(*str)[i[0]++] = '0';
		(*str)[i[0]++] = 'X';
		while (i[0] < fmt->precis - len + 2)
			(*str)[i[0]++] = '0';
		while (i[1] < (int)nbr_len)
			(*str)[i[0]++] = nbr[i[1]++];
		free(nbr);
		return ;
	}
	i[0] = ft_strlen(*str) - len - 1;
	i[1] = fmt->precis - len;
	while (i[1]-- && i[0] >= 0)
		(*str)[i[0]--] = '0';
	(*str)[i[0]--] = 'X';
	(*str)[i[0]] = '0';
}

static void		flag_plus_p(t_format *fmt, char **str)
{
	char		*res;
	int			i;

	if (!ft_strchr(fmt->flag, '+'))
		return ;
	if ((*str)[0] != ' ')
	{
		res = ft_strjoin("+", *str);
		free(*str);
		if (res[ft_strlen(res) - 1] == ' ')
			res[ft_strlen(res) - 1] = '\0';
		*str = res;
		return ;
	}
	i = 0;
	while ((*str)[i] == ' ')
		i++;
	(*str)[i - 1] = '+';
	return ;
}

static char		*str_p(t_format *fmt, char *nbr, int size, int ln)
{
	char	*str;
	int		i;

	str = ft_strnew(size);
	if (ft_strchr(fmt->flag, '-'))
	{
		ft_strcpy(str, nbr);
		i = ft_strlen(nbr);
		while (i < size)
			str[i++] = ' ';
	}
	else
	{
		i = 0;
		while (i < size - ln + 1)
			str[i++] = ' ';
		ft_strcpy(&str[--i], nbr);
	}
	(fmt->precis > 0 && fmt->precis < fmt->width) ? precis_p(&str, fmt, ln) : 0;
	(fmt->precis >= fmt->width) ? str = all_zero_p(nbr, fmt->precis, 0) : 0;
	if (ft_strchr(fmt->flag, '0') && fmt->width > ln
			&& !ft_strchr(fmt->flag, '-'))
		str = all_zero_p(nbr, fmt->width, 1);
	free(nbr);
	return (str);
}

/*
**	n:		n[0]: n				n[1]: size
*/

void			conv_p(t_lst *lst, t_chr **mychr, va_list ap)
{
	char		*str;
	char		*nbr;
	size_t		n[2];

	flag_star(lst->format, ap);
	n[0] = (flag_dollar(lst)) ?
		(size_t)va_arg(*(lst->arglist), void*) : (size_t)va_arg(ap, void*);
	if (n[0] == 0 && !lst->format->precis)
		(*mychr)->str = ft_strnew(0);
	else
	{
		nbr = ft_utoa_base(n[0], 16);
		flag_dash(&nbr, 16);
		flag_apostrophe(&nbr, lst->format);
		n[1] = ft_max(ft_strlen(nbr), lst->format->width);
		str = str_p(lst->format, nbr, n[1], (int)ft_strlen(nbr));
		if (ft_strchr(lst->format->flag, '0')
				&& lst->format->width > (int)ft_strlen(nbr)
				&& !ft_strchr(lst->format->flag, '-'))
			str = all_zero_p(nbr, lst->format->width, 1);
		(lst->format->convers == 'p') ? str = ft_strlowcase(str) : 0;
		flag_plus_p(lst->format, &str);
		(*mychr)->str = str;
	}
	(*mychr)->len = ft_strlen(str);
}