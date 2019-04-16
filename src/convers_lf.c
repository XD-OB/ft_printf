/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_ld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 03:59:42 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/15 16:34:35 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_entierld(long exp, t_ldouble db, t_format *format)
{
	long		new_exp;
	long		bin_mantis;
	char		*tab;
	char		*res;
	unsigned int	size;
	int		i;

	tab = NULL;
	size = 0;
	bin_mantis = db.zone.mantissa;
	new_exp = (exp == 0) ? 1 - LD_BIAS : exp - LD_BIAS;
	if (new_exp < 0)
		return (ft_strdup("0"));
	tab = (db.zone.int_b) ? int_add(tab, &size, 1) : int_add(tab, &size, 0);
	i = 63;
	while (--i >= 0 && new_exp > 0)
	{
		tab = (1 & (bin_mantis >> i)) ? int_add(tab, &size, 1) : int_add(tab, &size, 0);
		new_exp--;
	}
	while (new_exp > 0)
	{
		tab = int_add(tab, &size, 0);
		new_exp--;
	}
	i = -1;
	res = calcul_entier(tab, size, format);
	free(tab);
	return (res);
}

char		*get_fractld(long exp, t_ldouble db, t_format *format)
{
	int			len_b;
	unsigned int		size;
	char			*tab;
	char			*res;
	long			new_exp;
	long			bin_mantis;

	tab = NULL;
	size = 0;
	new_exp = (exp == 0) ? 1 - LD_BIAS : exp - LD_BIAS;
	bin_mantis = db.zone.mantissa;
	len_b = ABS(63 - new_exp - 1);
	if (len_b < 0)
		return (ft_strdup("0"));
	while (len_b >= 0)
	{
		if (new_exp < -1)
		{
			tab = int_add(tab, &size, 0);
			new_exp++;
		}
		else if (new_exp == -1)
		{
			tab = (db.zone.int_b) ? int_add(tab, &size, 1) : int_add(tab, &size, 0);
			new_exp++;
		}
		else
			tab = ((bin_mantis >> len_b) & 1) ? int_add(tab, &size, 1) : int_add(tab, &size, 0);
		len_b--;
	}
	res = calcul_fract(tab, size, format);
	free(tab);
	return (res);
}

void            conv_llf(t_lst *lst, t_chr **chr, va_list ap, int is_g)
{
	t_ldouble	db;
	unsigned int	len;
	char		*fract;
	char		*entier;
	char		*str;
	int		carry;

	carry = 0;
	flag_star(lst->format, ap);
	db.ld = (flag_dollar(lst)) ? va_arg(*(lst->arglist), long double) : va_arg(ap, long double);
	(lst->format->precis == -1) ? lst->format->precis = 6 : 0;
	if (pre_ld_calc(db, chr, lst, is_g))
		return ;
	entier = get_entierld(int_exp(db.zone.exponent, LD_BIAS), db, lst->format);
	flag_apostrophe(&entier, lst->format);
	fract = get_fractld(int_exp(db.zone.exponent, LD_BIAS), db, lst->format);
	if (is_g)
		lst->format->precis = ft_max(0, (lst->format->precis - (long)ft_strlen(entier)));
	fprecis(&fract, lst->format->precis, &carry, 10);
	(carry == 1) ? sumstr(&entier, "1", 10) : 0;
	str = ft_pointjoin(lst->format, entier, fract, &len);
	(lst->format->width > (int)len) ? customize_f(lst->format, &str, &len, db.zone.sign)
					: add_sign_f(lst->format, &str, &len, db.zone.sign);
	free(entier);
	free(fract);
	(*chr)->str = str;
	(*chr)->len = len;
}
