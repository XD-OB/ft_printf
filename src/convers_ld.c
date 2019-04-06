/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_ld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 03:59:42 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/06 04:05:32 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void            conv_llf(t_lst *lst, t_chr **mychr, va_list ap)
{
	t_ldouble                       db;
	char                            *fract;
	char                            *entier;
	unsigned int                    len_e;
	unsigned int                    len_f;
	unsigned int                    len;
	char                            *tmp;
	char                            *final;
	int                             carry;

	carry = 0;
	flag_star(lst->format, ap);
	db.ld = (flag_dollar(lst)) ? va_arg(*(lst->arglist), long double) : va_arg(ap, long double);
	(lst->format->precis == -1) ? lst->format->precis = 6 : 0;
	if (pre_ld_calc(db, mychr, lst))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, LD_BIAS), db.zone.mantissa, LD_BIAS, lst->format);
	flag_apostrophe(&entier, lst->format);
	fract = get_fract(int_exp(db.zone.exponent, LD_BIAS), db.zone.mantissa, LD_BIAS, lst->format);
	printf("\nfract before: %s\n", fract);
	fract = ft_fprecis(fract, lst->format->precis, &carry);
	ft_putchar('\n');
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
	if (ft_strchr(lst->format->flag, '#') || lst->format->precis != 0)
		tmp = ft_strjoin(entier, ".");
	else
		tmp = ft_strjoin(entier, "");
	final = (lst->format->precis > 0) ? ft_strjoin(tmp, fract) : ft_strjoin(tmp, "");
	printf("fract  : %s\n", fract);
	free(tmp);
	//free(fract);
	printf("entier: %s\n", entier);
	//free(entier);
	(*mychr)->str = final;
	(*mychr)->len = len;
}
