/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:38:44 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 13:48:51 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*custom_fannex(t_format *fmt, char *str, long *len, int sign)
{
	long	i;
	long	j;
	char	*res;

	j = *len;
	i = fmt->width;
	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (ft_strchr(fmt->flag, '0'))
	{
		while (j > 0)
			res[--i] = str[--j];
		while (i > 0)
			res[--i] = '0';
		if (sign)
			res[0] = '-';
		else if (ft_strchr(fmt->flag, '+'))
			res[0] = '+';
		else if (ft_strchr(fmt->flag, ' '))
			res[0] = ' ';
	}
	else
	{
		while (j > 0)
			res[--i] = str[--j];
		if (sign)
			res[--i] = '-';
		else if (ft_strchr(fmt->flag, '+'))
			res[--i] = '+';
		else if (ft_strchr(fmt->flag, ' '))
			res[--i] = ' ';
		while (i > 0)
			res[--i] = ' ';
	}
	*len = fmt->width;
	return (res);
}

/*
**	v[2]:		0: i		1: j
*/

void		customize_f(t_format *fmt, char **str, long *len, int sign)
{
	char	*res;
	long	v[2];

	if (ft_strchr(fmt->flag, '-'))
	{
		v[0] = 0;
		v[1] = 0;
		res = (char*)malloc(sizeof(char) * (fmt->width + 1));
		res[fmt->width] = '\0';
		if (sign)
			res[v[0]++] = '-';
		else if (ft_strchr(fmt->flag, '+'))
			res[v[0]++] = '+';
		else if (ft_strchr(fmt->flag, ' '))
			res[v[0]++] = ' ';
		while (v[1] < *len)
			res[v[0]++] = (*str)[v[1]++];
		*len = fmt->width;
		while (v[0] < *len)
			res[v[0]++] = ' ';
	}
	else
		res = custom_fannex(fmt, *str, len, sign);
	free(*str);
	*str = res;
}

void		conv_lfh(t_lst *lst, t_chr **chr, t_double db, int is_g)
{
	long	len;
	char	*fract;
	char	*entier;
	char	*str;
	char	*tmp;
	int		carry;
	int		base;

	carry = 0;
	base = (lst->format->convers == 'H') ? 16 : 10;
	if (pre_d_calc(db, chr, lst, is_g))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, lst->format);
	(base == 16) ? flag_dash(&entier, 16) : 0;
	flag_apostrophe(&entier, lst->format);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, lst->format);
	if (is_g)
		lst->format->precis =
			ft_max((lst->format->precis - ft_strlen(entier)), 1);
	fprecis(&fract, lst->format->precis, &carry, base);
	if (carry == 1)
	{
		tmp = entier;
		entier = ft_strsum(tmp, "1", base);
		free(tmp);
	}
	str = ft_pointjoin(lst->format, entier, fract, &len);
	(lst->format->width > (int)len) ?
		customize_f(lst->format, &str, &len, db.zone.sign) :
		add_sign_f(lst->format, &str, &len, db.zone.sign);
	free(entier);
	free(fract);
	(*chr)->str = str;
	(*chr)->len = len;
}
