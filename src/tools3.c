/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:49:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/12 01:09:41 by obelouch         ###   ########.fr       */
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
		n = (unsigned long int)va_arg(ap, unsigned long int);
	else if (ft_strstr(fmt->flag, "hh"))
		n = (unsigned char)va_arg(ap, unsigned int);
	else if (ft_strstr(fmt->flag, "h"))
		n = (unsigned short int)va_arg(ap, unsigned int);
	else if (ft_strstr(fmt->flag, "ll"))
		n = (unsigned long long int)va_arg(ap, unsigned long long int);
	else if (ft_strstr(fmt->flag, "l"))
		n = (unsigned long int)va_arg(ap, unsigned long int);
	else if (ft_strstr(fmt->flag, "z"))
		n = (size_t)va_arg(ap, size_t);
	else if (ft_strstr(fmt->flag, "j"))
		n = (size_t)va_arg(ap, uintmax_t);
	else
		n = (unsigned int)va_arg(ap, unsigned int);
	return (n);
}

char			*int_add(char *tab, unsigned int *oldsize, int data)
{
	char				*new;
	unsigned int		i;

	i = 0;
	new = ft_strnew(*oldsize + 1);
	while (i < *oldsize)
	{
		new[i] = tab[i];
		i++;
	}
	new[i] = data + '0';
	if (*oldsize != 0)
		free(tab);
	(*oldsize)++;
	return (new);
}

char			*ft_pointjoin(t_format *fmt, char *s1, char *s2, unsigned int *len)
{
	unsigned int	len_s1;
	unsigned int	len_s2;
	unsigned int	i;
	char		*str;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	*len = len_s1 + len_s2 + 1;
	if (len_s2 == 0 && !ft_strchr(fmt->flag, '#'))
		(*len)--;
	str = (char*)malloc(sizeof(char) * (*len + 1));
	str[*len] = '\0';
	i = 0;
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	if (i == *len)
		return (str);
	str[i] = '.';
	while (++i < *len)
		str[i] = s2[i - len_s1 - 1];
	return (str);
}
