/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_ld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 03:59:42 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/08 06:47:22 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_entierld(long exp, t_ldouble db, t_format *format)
{
	long	new_exp;
	long	bin_mantis;
	char	*tab;
	int		size_dec;
	int		i;

	tab = NULL;
	size_dec = 0;
	bin_mantis = db.zone.mantissa;
	new_exp = (exp == 0) ? 1 - LD_BIAS : exp - LD_BIAS;
	if (new_exp < 0)
		return (ft_strdup("0"));
	tab = (db.zone.int_b) ? int_addone(tab, size_dec, 1) : int_addone(tab, size_dec, 0);
	size_dec++;
	i = 63;
	while (--i >= 0 && new_exp > 0)
	{
		tab = (1 & (bin_mantis >> i)) ? int_addone(tab, size_dec, 1) : int_addone(tab, size_dec, 0);
		size_dec++;
		new_exp--;
	}
	while (new_exp > 0)
	{
		tab = int_addone(tab, size_dec, 0);
		size_dec++;
		new_exp--;
	}
	return (calcul_entier(tab, size_dec, format));
}

char		*get_fractld(long exp, t_ldouble db, t_format *format)
{
	int			len_b;
	unsigned int		size;
	char			*tab;
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
			tab = int_addone(tab, size, 0);
			size++;
			new_exp++;
		}
		else if (new_exp == -1)
		{
			tab = (db.zone.int_b) ?
				int_addone(tab, size, 1) : int_addone(tab, size, 0);
			size++;
			new_exp++;
		}
		else
		{
			tab = ((bin_mantis >> len_b) & 1) ?
				int_addone(tab, size, 1) : int_addone(tab, size, 0);
			size++;
		}
		len_b--;
	}
	return  (calcul_fract(tab, size, format));
}

void            conv_llf(t_lst *lst, t_chr **mychr, va_list ap)
{
	t_ldouble                       db;
	char                            *fract;
	char                            *entier;
	int             		       len_e;
	int         		           len_f;
	int   			               len;
	char                            *tmp;
	char                            *final;
	int                             carry;

	carry = 0;
	flag_star(lst->format, ap);
	db.ld = (flag_dollar(lst)) ? va_arg(*(lst->arglist), long double) : va_arg(ap, long double);
	(lst->format->precis == -1) ? lst->format->precis = 6 : 0;
	if (pre_ld_calc(db, mychr, lst))
		return ;
	entier = get_entierld(int_exp(db.zone.exponent, LD_BIAS), db, lst->format);
	flag_apostrophe(&entier, lst->format);
	fract = get_fractld(int_exp(db.zone.exponent, LD_BIAS), db, lst->format);
	fract = ft_fprecis(fract, lst->format->precis, &carry);
	if (carry == 1)
		entier = ft_strsum(entier, "1", 10);
	if (db.zone.sign)
		entier = add_sign(entier, (int)(db.zone.sign));
	len_e = ft_strlen(entier);
	len_f = ft_strlen(fract);
	len = len_e + len_f + 1;
	if (lst->format->width > (int)len && !ft_strchr(lst->format->flag, '-'))
	{
		entier = ft_fwidth(entier, len_e, lst->format, len_f);
		len = lst->format->width;
	}
	else if (ft_strchr(lst->format->flag, ' ') && !ft_strchr(lst->format->flag, '-'))
		flag_space(&entier, lst->format->flag);
	len_e = ft_strlen(entier);
	tmp = (ft_strchr(lst->format->flag, '#') || lst->format->precis != 0) ?
		ft_strjoin(entier, ".") : ft_strdup(entier);
	final = (lst->format->precis > 0) ? ft_strjoin(tmp, fract) : ft_strjoin(tmp, "");
	free(tmp);
	free(fract);
	free(entier);
	(*mychr)->str = final;
	(*mychr)->len = len;
}

