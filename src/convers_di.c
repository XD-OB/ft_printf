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

static void		di_zero(t_chr **chr, t_format *fmt)
{
	char		*nbr;
	char		*res;
	int		len_nbr;
	char		c;
	int		i;
	int		j;

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
		res = (char*)malloc(sizeof(char) * (fmt->width + 1));
		res[fmt->width] = '\0';
		if (ft_strchr(fmt->flag, '-'))
		{
			i = -1;
			while (++i < len_nbr)
				res[i] = nbr[i];
			while (i < fmt->width)
				res[i++] = ' ';
		}
		else
		{
			c = (ft_strchr(fmt->flag, '0') && fmt->precis == 1) ? '0' : ' ';
			i = fmt->width - 1;
			j = len_nbr - 1;
			while (j >= 0)
				res[i--] = nbr[j--];
			while (i >= 0)
				res[i--] = c;
			if (c == '0' && ft_strpbrk(fmt->flag, "+ "))
			{
				res[0] = (ft_strchr(fmt->flag, '+')) ? '+' : ' ';
				res[fmt->width - len_nbr] = '0';
			}
		}
		free(nbr);
		(*chr)->str = res;
		(*chr)->len = fmt->width;
	}
	else
	{
		(*chr)->str = nbr;
		(*chr)->len = len_nbr;
	}
}

static void		di_n(t_chr **chr, t_format *fmt, char *num, int sign)
{
	char		*nbr;
	char		*res;
	int		len_nbr;
	int		len_num;
	char		c;
	int		i;
	int		j;

	len_num = ft_strlen(num);
	len_nbr = ft_max(fmt->precis, len_num);
	if (sign == -1 || ft_strpbrk(fmt->flag, "+ "))
		len_nbr++;
	nbr = (char*)malloc(sizeof(char) * (len_nbr + 1));
	nbr[len_nbr] = '\0';
	i = len_nbr;
	j = len_num;
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
	if (fmt->width > len_nbr)
	{
		res = (char*)malloc(sizeof(char) * (fmt->width + 1));
		res[fmt->width] = '\0';
		if (ft_strchr(fmt->flag, '-'))
		{
			i = -1;
			while (++i < len_nbr)
				res[i] = nbr[i];
			while (i < fmt->width)
				res[i++] = ' ';
		}
		else
		{
			c = (ft_strchr(fmt->flag, '0') && fmt->precis == -1) ? '0' : ' ';
			i = fmt->width - 1;
			j = len_nbr - 1;
			while (j >= 0)
				res[i--] = nbr[j--];
			while (i >= 0)
				res[i--] = c;
			if (c == '0' && (ft_strpbrk(fmt->flag, "+ ") || sign == -1))
			{
				if (sign == -1)
					res[0] = '-';
				else
					res[0] = (ft_strchr(fmt->flag, '+')) ? '+' : ' ';
				res[fmt->width - len_nbr] = '0';
			}
		}
		free(nbr);
		(*chr)->str = res;
		(*chr)->len = fmt->width;
	}
	else
	{
		(*chr)->str = nbr;
		(*chr)->len = len_nbr;
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

