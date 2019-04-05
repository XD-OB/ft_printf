/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:15:28 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/05 05:26:00 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long int	cast_di(va_list ap, char *flag)
{
	long long int		d;

	if (ft_strstr(flag, "hh"))
		d = (char)va_arg(ap, int);
	else if (ft_strstr(flag, "h"))
		d = (short int)va_arg(ap, int);
	else if (ft_strstr(flag, "ll"))
		d = va_arg(ap, long long int);
	else if (ft_strstr(flag, "l"))
		d = va_arg(ap, long int);
	else
		d = (int)va_arg(ap, int);
	return (d);
}

/*
**	len:	len[0]: size		len[1]: nbr_size		len[2]: i
*/

static void				fill_di_str(t_chr **mychr, t_format *fmt, char *nbr,
								long long int d)
{
	size_t				len[3];
	char				*str;

	len[1] = ft_strlen(nbr);
	len[0] = ft_max(fmt->width, fmt->precis);
	len[0] = ft_max(len[0], len[1]);
	if (!(str = ft_strnew(len[0])))
		return ;
	len[2] = 0;
	while (len[2] < (len[0] - len[1]))
		str[(len[2])++] = (ft_strchr(fmt->flag, '0')) ? '0' : ' ';
	if (d < 0 && ft_strchr(fmt->flag, '0'))
	{
		nbr[0] = '0';
		str[0] = '-';
	}
	ft_strcat(str, nbr);
	if (ft_strchr(fmt->flag, '0') && fmt->width > (int)len[1] && !fmt->precis)
		zero_dbiou(&str, fmt);
	if (fmt->precis > 0)
		precis_o_udi(&str, fmt, len[1]);
	(*mychr)->str = str;
	(*mychr)->len = len[0];
}

void					conv_di(t_lst *lst, t_chr **mychr, va_list ap)
{
	char				*nbr;
	long long int		d;

	flag_star(lst->format, ap);
	if (flag_dollar(lst))
		d = cast_di(*(lst->arglist), lst->format->flag);
	else
		d = cast_di(ap, lst->format->flag);
	if (d == 0 && !lst->format->precis)
	{
		(*mychr)->str = ft_strnew(0);
		(*mychr)->len = 0;
	}
	else
	{
		nbr = ft_itoa(d);
		flag_apostrophe(&nbr, lst->format);
		if (ft_strchr(lst->format->flag, '+'))
			flag_plus(&nbr, lst->format->convers);
		if (d >= 0 && ft_strchr(lst->format->flag, ' '))
			flag_space(&nbr, lst->format->flag);
		fill_di_str(mychr, lst->format, nbr, d);
		free(nbr);
	}
}
