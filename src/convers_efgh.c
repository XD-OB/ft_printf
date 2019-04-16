/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_efgh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:57:10 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/08 01:25:18 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			gclean(t_format *fmt, t_chr **mychr)
{
	char	*clean;
	int		size;
	int		i;

	if (!ft_strchr(fmt->flag, '#'))
	{
		size = (*mychr)->len - 1;
		while (size >= 0 && ((*mychr)->str)[size] == '0')
			size--;
		if (((*mychr)->str)[size] == '.')
			size--;
		if (size != (int)((*mychr)->len))
		{
			clean = (char*)malloc(sizeof(char) * size + 2);
			clean[size + 1] = '\0';
			i = -1;
			while (++i <= size)
				clean[i] = ((*mychr)->str)[i];
			free((*mychr)->str);
			(*mychr)->str = clean;
			(*mychr)->len = size + 1;
		}
	}
}

void			conv_d_efgh(t_lst *lst, t_chr **mychr, va_list ap)
{
	t_double	db;
	int		is_long;
	int		exp;

	is_long = (ft_strchr(lst->format->flag, 'L') ? 1 : 0);
	flag_star(lst->format, ap);
	db.d = (flag_dollar(lst)) ?
			va_arg(*(lst->arglist), double) : va_arg(ap, double);
	(lst->format->precis == -1) ? lst->format->precis = 6 : 0;
	if (ft_strchr("fH", lst->format->convers))
		(is_long) ? conv_llf(lst, mychr, ap, 0) : conv_lfh(lst, mychr, db, 0);
	else if (ft_strchr("eE", lst->format->convers))
		(is_long) ? conv_lee(lst, mychr, ap, 0) : conv_ee(lst, mychr, db, 0);
	else
	{
		//(lst->format->precis == 0) ? lst->format->precis++ : 0;
		if (ft_strchr(lst->format->flag, '#'))
			lst->format->precis = 6;
		exp = int_exp(db.zone.mantissa, (is_long) ? LD_BIAS : D_BIAS);
		if (exp < -4 || exp >= (int)(lst->format->precis))
		{
			if (lst->format->convers == 'G')
				lst->format->convers = 'E';
			(is_long) ? conv_lee(lst, mychr, ap, 1) : conv_ee(lst, mychr, db, 1);
		}
		else
			(is_long) ? conv_llf(lst, mychr, ap, 1) : conv_lfh(lst, mychr, db, 1);
		//gclean(lst->format, mychr);
	}
}
