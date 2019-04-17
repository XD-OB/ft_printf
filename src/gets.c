/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:34:52 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 13:35:07 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_entier(long exp, long bin_mantis, int bias, t_format *format)
{
	unsigned long long	m;
	unsigned int		v[2];
	long				new_exp;
	char				*tab;
	char				*res;

	v[0] = 0;
	v[1] = 0;
	tab = NULL;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	if (new_exp < 0)
		return (ft_strdup("0"));
	m = 2251799813685248;
	(exp) ? int_add(&tab, &v[0], 1) : int_add(&tab, &v[0], 0);
	while ((v[1])++ < new_exp)
	{
		(m & bin_mantis) ? int_add(&tab, &v[0], 1) : int_add(&tab, &v[0], 0);
		m >>= 1;
	}
	res = calcul_entier(tab, v[0], format);
	free(tab);
	return (res);
}

static int	fill_tab(char **tab, unsigned int *size, long *new_exp, long exp)
{
	if (*new_exp < -1)
	{
		int_add(tab, size, 0);
		(*new_exp)++;
		return (0);
	}
	if (*new_exp == -1)
	{
		(exp) ? int_add(tab, size, 1) : int_add(tab, size, 0);
		(*new_exp)++;
		return (0);
	}
	return (1);
}

char		*get_fract(long exp, long bin_mantis, int bias, t_format *format)
{
	unsigned int	size;
	long			new_exp;
	int				len_b;
	char			*tab;
	char			*res;

	tab = NULL;
	size = 0;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	len_b = ABS(52 - new_exp - 1);
	if (len_b < 0)
		return (ft_strdup("0"));
	while (len_b >= 0)
	{
		if (fill_tab(&tab, &size, &new_exp, exp))
			((bin_mantis >> len_b) & 1) ?
				int_add(&tab, &size, 1) : int_add(&tab, &size, 0);
		len_b--;
	}
	res = calcul_fract(tab, size, format);
	free(tab);
	return (res);
}
