/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:15:28 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/09 07:50:11 by obelouch         ###   ########.fr       */
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
	else if (ft_strstr(flag, "j"))
		d = va_arg(ap, intmax_t);
	else
		d = (int)va_arg(ap, int);
	return (d);
}

static int		sign_n(long long int n)
{
	if (n > 0)
		return (1);
	if (n < 0)
		return (-1);
	return (0);
}

static int		w_di_annex(char **res, t_format *fmt, char *nbr, int len_nbr)
{
	int		i;

	if (ft_strchr(fmt->flag, '-'))
	{
		i = -1;
		while (++i < len_nbr)
			(*res)[i] = nbr[i];
		while (i < fmt->width)
			(*res)[i++] = ' ';
		return (1);
	}
	return (0);
}

static char		*width_di(t_format *fmt, char *nbr, int len_nbr, int sign)
{
	int	z;
	char	*res;
	int	i;
	int	j;
	char	c;

	z = (sign == 0) ? 1 : -1;
	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (w_di_annex(&res, fmt, nbr, len_nbr) == 1)
		return (res);
	c = (ft_strchr(fmt->flag, '0') && fmt->precis == z) ? '0' : ' ';
	i = fmt->width - 1;
	j = len_nbr - 1;
	while (j >= 0)
		res[i--] = nbr[j--];
	while (i >= 0)
		res[i--] = c;
	if (c == '0' && (ft_strpbrk(fmt->flag, "+ ") || sign == -1))
	{
		res[0] = (sign == -1) ? '-' :
			((ft_strchr(fmt->flag, '+')) ? '+' : ' ');
		res[fmt->width - len_nbr] = '0';
	}
	return (res);
}

static void		di_zero(t_chr **chr, t_format *fmt)
{
	char		*nbr;
	int		len_nbr;

	if (fmt->precis == -1)
		fmt->precis = 1;
	len_nbr = fmt->precis;
	if (ft_strpbrk(fmt->flag, "+ "))
		len_nbr++;
	nbr = ft_strcnew(len_nbr, '0');
	if (ft_strchr(fmt->flag, '+'))
		nbr[0] = '+';
	else if (ft_strchr(fmt->flag, ' '))
		nbr[0] = ' ';
	if (fmt->width > len_nbr)
	{
		(*chr)->str = width_di(fmt, nbr, len_nbr, 0);
		(*chr)->len = fmt->width;
		free(nbr);
	}
	else
	{
		(*chr)->str = nbr;
		(*chr)->len = len_nbr;
	}
}

/*
** len[2]       0: len_nbr		1: len_num
*/

static char		*di_nbr(t_format *fmt, char *num, int *len, int sign)
{
	char		*nbr;
	int		i;
	int		j;

	nbr = (char*)malloc(sizeof(char) * (len[0] + 1));
	nbr[len[0]] = '\0';
	i = len[0];
	j = len[1];
	while (--j >= 0)
		nbr[--i] = num[j];
	while (--i >= 0)
		nbr[i] = '0';
	if (sign == -1)
		nbr[0] = '-';
	else if (ft_strchr(fmt->flag, '+'))
		nbr[0] = '+';
	else if (ft_strchr(fmt->flag, ' '))
		nbr[0] = ' ';
	return (nbr);
}

static void		di_n(t_chr **chr, t_format *fmt, char *num, int sign)
{
	char		*nbr;
	int		len[2];

	len[1] = ft_strlen(num);
	len[0] = ft_max(fmt->precis, len[1]);
	if (sign == -1 || ft_strpbrk(fmt->flag, "+ "))
		len[0]++;
	nbr = di_nbr(fmt, num, len, sign);
	if (fmt->width > len[0])
	{
		(*chr)->str = width_di(fmt, nbr, len[0], sign);
		(*chr)->len = fmt->width;
		free(nbr);
	}
	else
	{
		(*chr)->str = nbr;
		(*chr)->len = len[0];
	}
}

void			conv_di(t_lst *lst, t_chr **chr, va_list ap)
{
	long long int	n;
	int		sign;
	char		*num;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ?
		cast_di(*(lst->arglist), lst->format->flag) : cast_di(ap, lst->format->flag);
	sign = sign_n(n);
	if (sign == 0)
		di_zero(chr, lst->format);
	else
	{
		num = ft_poslltoa(n);
		di_n(chr, lst->format, num, sign);
		free(num);
		num = NULL;
	}
}
