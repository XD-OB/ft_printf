/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_efgh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:57:10 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/03 17:59:56 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

double			ft_dpow(int a, int b)
{
	long long	res;

	res = 1;
	if (a == 0)
		return (0);
	if (b > 0)
	{
		while (b-- >= 0)
			res *= a;
	}
	return (res);
}

void			gclean(t_chr **mychr)
{
	char			*clean;
	unsigned int	size;
	unsigned int	i;

	size = (*mychr)->len - 1;
	while (size >= 0 && ((*mychr)->str)[size] == '0')
		size--;
	if (((*mychr)->str)[size] == '.')
		size--;
	if (size != (*mychr)->len)
	{
		clean = (char*)malloc(sizeof(char) * size + 2);
		clean[size + 1] = '\0';
		i = 0;
		while (i <= size)
		{
			clean[i] = ((*mychr)->str)[i];
			i++;
		}
		free((*mychr)->str);
		(*mychr)->str = clean;
		(*mychr)->len = size + 1;
	}
}

void			conv_d_efgh(t_lst *lst, t_chr **mychr, va_list ap)
{
	t_double	db;

	flag_star(lst->format, ap);
	db.d = (flag_dollar(lst)) ?
			va_arg(*(lst->arglist), double) : va_arg(ap, double);
	(lst->format->precis == -1) ? lst->format->precis = 6 : 0;
	if (ft_strchr("fH", lst->format->convers))
		conv_lfh(lst, mychr, db);
	else if (ft_strchr("eE", lst->format->convers))
		conv_ee(lst, mychr, db);
	else
	{
		if (lst->format->precis == 0)
			lst->format->precis++;
		if (db.d < 0.001 || db.d >= ft_dpow(10, lst->format->precis))
		{
			if (lst->format->convers == 'G')
				lst->format->convers = 'E';
			conv_ee(lst, mychr, db);
		}
		else
			conv_lfh(lst, mychr, db);
		gclean(mychr);
	}
}
