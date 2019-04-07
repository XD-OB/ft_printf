/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:49:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/07 05:08:14 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*foisdix(char *str, unsigned int len)
{
	char			*new;
	unsigned int	i;

	i = 0;
	new = ft_strnew(len  + 1);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '0';
	free(str);
	return (new);
}

unsigned long long int		cast_xxoub(va_list ap, t_format *fmt)
{
	unsigned long long int	n;

	if (fmt->convers == 'U')
		n = (unsigned long int)va_arg(ap, unsigned int);
	else if (ft_strstr(fmt->flag, "hh"))
		n = (unsigned char)va_arg(ap, unsigned int);
	else if (ft_strstr(fmt->flag, "h"))
		n = (unsigned short int)va_arg(ap, unsigned int);
	else if (ft_strstr(fmt->flag, "ll"))
		n = (unsigned long long int)va_arg(ap, unsigned long long int);
	else if (ft_strstr(fmt->flag, "l"))
		n = (unsigned long int)va_arg(ap, unsigned long int);
	else
		n = (unsigned int)va_arg(ap, unsigned int);
	return (n);
}
