/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:27:28 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 09:41:46 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*ft_strzero(t_format *fmt, unsigned int *len, int is_g)
{
	char			*res;

	if (is_g && (!ft_strchr(fmt->flag, '#') || !fmt->precis))
		*len = 1;
	else
	{
		if (is_g)
			fmt->precis = ft_max(fmt->precis - 1, 0);
		*len = fmt->precis + 1;
	}
	(*len > 1 || ft_strchr(fmt->flag, '#')) ? (*len)++ : 0;
	res = ft_strcnew(*len, '0');
	if (*len > 1)
		res[1] = '.';
	return (res);
}

int					pre_d_calc(t_double db, t_chr **chr, t_lst *lst, int is_g)
{
	char			*str;
	char			*tmp;
	unsigned int	len;

	if (!int_mants(db.zone.mantissa, D_BIAS) &&
		!int_exp(db.zone.exponent, D_BIAS))
	{
		str = ft_strzero(lst->format, &len, is_g);
		if (ft_strchr("eE", lst->format->convers))
		{
			tmp = ft_strjoin(str, "e+00");
			free(str);
			str = tmp;
			len += 4;
		}
		(lst->format->width > (int)len) ?
			customize_f(lst->format, &str, &len, db.zone.sign) :
			add_sign_f(lst->format, &str, &len, db.zone.sign);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	if (!int_mants(db.zone.mantissa, D_BIAS) &&
		(int_exp(db.zone.exponent, D_BIAS) >= MAX_D))
	{
		str = ft_strdup("inf");
		len = 3;
		(lst->format->width > (int)len) ?
			custom_inff(lst->format, &str, &len, db.zone.sign) :
			add_sign_f(lst->format, &str, &len, db.zone.sign);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	if (int_mants(db.zone.mantissa, D_BIAS) &&
		(int_exp(db.zone.exponent, D_BIAS) >= MAX_D))
	{
		str = ft_strdup("nan");
		len = 3;
		if (lst->format->width > (int)len)
			custom_nanf(lst->format, &str, &len);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	return (0);
}

int					pre_ld_calc(t_ldouble db, t_chr **chr, t_lst *lst, int is_g)
{
	char			*str;
	char			*tmp;
	unsigned int	len;

	if (is_g)
		lst->format->precis = ft_max(lst->format->precis - 1, 0);
	if (!int_mants(db.zone.mantissa, LD_BIAS) &&
		!int_exp(db.zone.exponent, LD_BIAS))
	{
		str = ft_strzero(lst->format, &len, is_g);
		if (ft_strchr("eE", lst->format->convers))
		{
			tmp = ft_strjoin(str, "e+00");
			free(str);
			str = tmp;
			len += 4;
		}
		(lst->format->width > (int)len) ?
			customize_f(lst->format, &str, &len, db.zone.sign) :
			add_sign_f(lst->format, &str, &len, db.zone.sign);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	if (!int_mants(db.zone.mantissa, LD_BIAS) &&
		(int_exp(db.zone.exponent, LD_BIAS) >= MAX_LD))
	{
		str = ft_strdup("inf");
		len = 3;
		(lst->format->width > (int)len) ?
			custom_inff(lst->format, &str, &len, db.zone.sign) :
			add_sign_f(lst->format, &str, &len, db.zone.sign);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	if (int_mants(db.zone.mantissa, LD_BIAS) &&
		(int_exp(db.zone.exponent, LD_BIAS) >= MAX_LD))
	{
		str = ft_strdup("nan");
		len = 3;
		if (lst->format->width > (int)len)
			custom_nanf(lst->format, &str, &len);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	return (0);
}
