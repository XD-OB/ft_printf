/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_xb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 04:08:02 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/07 05:08:50 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char                    *all_zero_xb(char *nbr, int precis, int dash, int width, int base)
{
	char    *res;
	int             len;
	int             len_nbr;
	int             i;
	int             j;

	len_nbr = (int)ft_strlen(nbr);
	len = ft_max(precis, len_nbr);
	if (dash && !width)
		len += 2;
	res = ft_strnew(len);
	i = 0;
	j =  0;
	if (dash)
	{
		len_nbr -= 2;
		res[i++] = '0';
		res[i++] = (base == 2) ? 'b' : 'x';
		j = 2;
	}
	while (i < (len - len_nbr))
		res[i++] = '0';
	while (i < len)
		res[i++] = nbr[j++];
	return (res);
}

void                    precis_xb(char **str, t_format *fmt, size_t nbr_len, int base)
{
	int             i;
	int             j;
	int             len;
	char    *nbr;

	len = (ft_strchr(fmt->flag, '#')) ? (nbr_len - 2) : nbr_len;
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		nbr = ft_strdup(*str);
		if (ft_strchr(fmt->flag, '#'))
		{
			j = 2;
			(*str)[i++] = '0';
			(*str)[i++] = (base == 2) ? 'b' : 'x';
		}
		while (i < fmt->precis - len)
			(*str)[i++] = '0';
		while(j < len)
			(*str)[i++] = nbr[j++];
		free(nbr);
	}
	else
	{
		i = ft_strlen(*str) - len - 1;
		j = fmt->precis - len;
		while (j-- && i >= 0)
			(*str)[i--] = '0';
		if (ft_strchr(fmt->flag, '#'))
		{
			(*str)[i--] = 'x';
			(*str)[i] = '0';
		}
	}
}

void                    conv_xx(t_lst *lst, t_chr **mychr, va_list ap)
{
	size_t          size;
	char            *str;
	char            *nbr;
	size_t          n;
	int                     i;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format)
		: cast_xxoub(ap, lst->format);
	if (n == 0 && !lst->format->precis)
	{
		(*mychr)->str = ft_strcnew(lst->format->width, ' ');
		((*mychr)->str)[lst->format->width] = '\0';
		(*mychr)->len = lst->format->width;
		return ;
	}
	nbr = ft_utoa_base(n, 16);
	if (n && ft_strchr(lst->format->flag, '#'))
		flag_dash(&nbr, 16);
	flag_apostrophe(&nbr, lst->format);
	size = ft_max(ft_strlen(nbr), lst->format->width);
	if (!(str = ft_strnew(size)))
		return ;
	if (ft_strchr(lst->format->flag, '-'))
	{
		ft_strcpy(str, nbr);
		i = ft_strlen(nbr);
		while (i < (int)size)
			str[i++] = ' ';
	}
	else
	{
		i = 0;
		while (i < (int)(size - ft_strlen(nbr) + 1))
			str[i++] = ' ';
		ft_strcpy(&str[--i], nbr);
	}
	if (ft_strchr(lst->format->flag, '0') && lst->format->precis > 0
			&& lst->format->precis < lst->format->width)
		precis_xb(&str, lst->format, ft_strlen(nbr), 16);
	if (lst->format->precis >= lst->format->width)
		str = all_zero_xb(nbr, lst->format->precis,
			(ft_strchr(lst->format->flag, '#')) ? 1 : 0, 0, 16);
	if (ft_strchr(lst->format->flag, '0')
			&& lst->format->width > (int)ft_strlen(nbr)
			&& !ft_strchr(lst->format->flag, '-') && lst->format->precis <= 0)
		str = all_zero_xb(nbr, lst->format->width,
				(ft_strchr(lst->format->flag, '#')) ? 1 : 0, 1, 16);
	(lst->format->convers == 'x') ? str = ft_strlowcase(str) : 0;
	(lst->format->convers == 'X') ? str = ft_strupcase(str) : 0;
	(*mychr)->str = str;
	free(nbr);
	(*mychr)->len = ft_strlen(str);
}

void                    conv_b(t_lst *lst, t_chr **mychr, va_list ap)
{
	size_t          size;
	char            *str;
	char            *nbr;
	size_t          n;
	int                     i;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format)
		: cast_xxoub(ap, lst->format);
	if (n == 0 && !lst->format->precis)
		(*mychr)->str = ft_strnew(0);
	else
	{
		nbr = ft_utoa_base(n, 2);
		if (n && ft_strchr(lst->format->flag, '#'))
			flag_dash(&nbr, 2);
		flag_apostrophe(&nbr, lst->format);
		size = ft_max(ft_strlen(nbr), lst->format->width);
		if (!(str = ft_strnew(size)))
			return ;
		if (ft_strchr(lst->format->flag, '-'))
		{
			ft_strcpy(str, nbr);
			i = ft_strlen(nbr);
			while (i < (int)size)
				str[i++] = ' ';
		}
		else
		{
			i = 0;
			while (i < (int)(size - ft_strlen(nbr) + 1))
				str[i++] = ' ';
			ft_strcpy(&str[--i], nbr);
		}
		if (ft_strchr(lst->format->flag, '0') && lst->format->precis > 0
				&& lst->format->precis < lst->format->width)
			precis_xb(&str, lst->format, ft_strlen(nbr), 2);
		if (lst->format->precis >= lst->format->width)
			str = all_zero_xb(nbr, lst->format->precis, (ft_strchr(lst->format->flag, '#')) ? 1 : 0, 0, 2);
		if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr) && !ft_strchr(lst->format->flag, '-'))
			str = all_zero_xb(nbr, lst->format->width, (ft_strchr(lst->format->flag, '#')) ? 1 : 0, 1, 2);
		(lst->format->convers == 'b') ? str = ft_strlowcase(str) : 0;
		(lst->format->convers == 'B') ? str = ft_strupcase(str) : 0;
		(*mychr)->str = str;
		free(nbr);
	}
	(*mychr)->len = ft_strlen(str);
}
