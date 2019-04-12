/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_xxoub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:35:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/12 02:39:35 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*o_zerores(t_format *fmt, char *nbr, int len_nbr, char c)
{
	char		*res;
	int			i;
	int			j;

	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (!ft_strchr(fmt->flag, '-'))
	{
		i = fmt->width;
		j = len_nbr;
		while (--j >= 0)
			res[--i] = nbr[j];
		while (--i >= 0)
			res[i] = c;
	}
	else
	{
		i = 0;
		j = 0;
		while (j < len_nbr)
			res[i++] = nbr[j++];
		while (i < fmt->width)
			res[i++] = c;
	}
	return (res);
}

static char		*o_zero(t_format *fmt)
{
	char		*res;
	int			len_nbr;
	char		*nbr;
	char		c;

	len_nbr = fmt->precis;
	if (fmt->precis == -1
			|| (!fmt->precis && ft_strchr(fmt->flag, '#')))
		len_nbr = 1;
	nbr = ft_strcnew(len_nbr, '0');
	if (fmt->width > len_nbr)
	{
		c = (fmt->precis == -1 && ft_strchr(fmt->flag, '0')
				&& !ft_strchr(fmt->flag, '-')) ? '0' : ' ';
		res = o_zerores(fmt, nbr, len_nbr, c);
		free(nbr);
		return (res);
	}
	return (nbr);
}

static char		*o_nbr(t_format *fmt, char *num, int len_num, int *len_nbr)
{
	char		*nbr;
	int			dash;
	int			i;
	int			j;

	dash = (ft_strchr(fmt->flag, '#')) ? 1 : 0;
	*len_nbr = ft_max(len_num + dash, fmt->precis);
	nbr = (char*)malloc(sizeof(char) * (*len_nbr + 1));
	nbr[*len_nbr] = '\0';
	i = *len_nbr;
	j = len_num;
	while (--j >= 0)
		nbr[--i] = num[j];
	while (--i >= 0)
		nbr[i] = '0';
	return (nbr);
}

static char		*o_nres(t_format *fmt, char *nbr, int len_nbr, char c)
{
	char		*res;
	int			i;
	int			j;

	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (!ft_strchr(fmt->flag, '-'))
	{
		i = -1;
		while (++i < fmt->width - len_nbr)
			res[i] = c;
		j = -1;
		while (++j < len_nbr)
			res[i++] = nbr[j];
	}
	else
	{
		i = 0;
		j = 0;
		while (j < len_nbr)
			res[i++] = nbr[j++];
		while (i < fmt->width)
			res[i++] = ' ';
	}
	return (res);
}

static char		*o_n(t_format *fmt, char *num, int len_num)
{
	char		*res;
	char		*nbr;
	int			len_nbr;
	char		c;

	nbr = o_nbr(fmt, num, len_num, &len_nbr);
	if (fmt->width - len_nbr > 0)
	{
		c = (fmt->precis == -1 && ft_strchr(fmt->flag, '0')
				&& !ft_strchr(fmt->flag, '-')) ? '0' : ' ';
		res = o_nres(fmt, nbr, len_nbr, c);
		free(nbr);
		return (res);
	}
	return (nbr);
}

void			conv_o(t_lst *lst, t_chr **chr, va_list ap)
{
	unsigned long long int	n;
	char					*num;
	char					*res;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format)
		: cast_xxoub(ap, lst->format);
	if (n == 0)
		res = o_zero(lst->format);
	else
	{
		num = ft_ulltoa_base(n, 8);
		res = o_n(lst->format, num, (int)ft_strlen(num));
		free(num);
	}
	(*chr)->str = res;
	(*chr)->len = ft_strlen(res);
}
