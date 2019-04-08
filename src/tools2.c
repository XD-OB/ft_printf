/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 04:07:35 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/08 03:31:54 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_format(char c)
{
	char	*ref;
	int		i;

	i = 0;
	ref = "cspdiouUxXfegrkb}%";
	while (ref[i])
		if (c == ref[i++])
			return (1);
	return (0);
}

int			is_postflag(char c)
{
	char	*ref;
	int		i;

	i = 0;
	ref = "lLh+-rjz";
	while (ref[i])
		if (c == ref[i++])
			return (1);
	return (0);
}

int			is_preflag(char c)
{
	char	*ref;
	int		i;

	i = 0;
	ref = " 0+-#'*$r";
	while (ref[i])
		if (c == ref[i++])
			return (1);
	return (0);
}

void		put_spstr(char *str)
{
	while (*str)
	{
		if (*str != '%')
			ft_putchar(*str);
		str++;
	}
}

char		*cut_str(char *str, int p1, int p2)
{
	char	*ret;
	int		i;

	i = p1 - 1;
	if (!(ret = ft_strnew(p2 - p1 + 1)))
		return (0);
	while (++i <= p2)
		ret[i - p1] = str[i];
	return (ret);
}
