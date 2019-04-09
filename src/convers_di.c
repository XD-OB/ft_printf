/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:15:28 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/09 03:12:20 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long int	cast_di(va_list ap, char *flag)
{
	long long int		d;

	if (ft_strstr(flag, "hh"))
		d = (char)va_arg(ap, int);
	else if (ft_strstr(flag, "h"))
		d = (short int)va_arg(ap, int);
	else if (ft_strstr(flag, "ll"))
		d = va_arg(ap, long long int);
	else if (ft_strstr(flag, "l"))
		d = va_arg(ap, long int);
	else if (ft_strstr(flag, "j"))
		d = va_arg(ap, intmax_t);
	else
		d = (int)va_arg(ap, int);
	return (d);
}

char                    *all_zero_di(char *nbr, int precis, int is_width)
{
	char    *res;
	int             len;
	int             len_nbr;
	int             i;
	int             j;

	len = precis;
	if (nbr[0] == '-' && !is_width)
		len++;
	len_nbr = (nbr[0] == '-') ? (int)ft_strlen(nbr) - 1
		: (int)ft_strlen(nbr);
	res = ft_strnew(len);
	i = 0;
	j =  0;
	while (i < (len - len_nbr))
		res[i++] = '0';
	if (nbr[0] == '-')
	{
		res[0] = '-';
		j++;
	}
	while (j < (int)ft_strlen(nbr))
		res[i++] = nbr[j++];
	return (res);
}

void                    precis_di(char **str, t_format *fmt, size_t nbr_len)
{
	int             i;
	int             j;
	char    *nbr;

	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		nbr = ft_strdup(*str);
		while (i < fmt->precis - (int)nbr_len)
			(*str)[i++] = '0';
		if ((*str)[i] == '-')
		{
			(*str)[0] = '-';
			(*str)[i++] = '0';
		}
		while (i < fmt->precis - (int)nbr_len)
			(*str)[i++] = '0';
		while(j < (int)nbr_len)
			(*str)[i++] = nbr[j++];
		free(nbr);
	}
	else
	{
		i = ft_strlen(*str) - nbr_len - 1;
		j = fmt->precis - nbr_len;
		while (--j >= 0 && i >= 0)
			(*str)[i--] = '0';
		i = ft_strlen(*str) - nbr_len;
		if ((*str)[i] == '-')
		{
			(*str)[i] = '0';
			j = i;
			while ((*str)[j] == '0')
				j--;
			(*str)[j] = '-';
		}
	}
}

static void		flag_plusp_di(t_format *fmt, char **str, int len_nbr, char x)
{
	int			len_str;
	char		*res;
	int			i;

	len_str = ft_strlen(*str);
	if (ft_strchr(fmt->flag, '-'))
	{
		if (len_nbr > ft_max (fmt->precis, fmt->width))
			len_str++;
		res = ft_strnew(len_str);
		res[0] = x;
		ft_strncpy(&res[1], *str, len_str - 1);
		free (*str);
		*str = res;
	}
	else
	{
		if (ft_strchr(fmt->flag, '0'))
		{
			if (fmt->width > len_nbr ||  fmt->precis > len_nbr)
				(*str)[0] = x;
			else
			{
				res = ft_strnew(len_str + 1);
				res[0] = x;
				ft_strncpy(&res[1], *str, len_str);
				free (*str);
				*str = res;
			}
		}
		else
		{
			if (fmt->width > len_nbr)
			{
				i = 0;
				while ((*str)[i] != ' ')
					i++;
				(*str)[i - 1] = x;
			}
			else if (fmt->precis > len_nbr)
				(*str)[0] = x;
			else
			{
				res = ft_strnew(len_str + 1);
				res[0] = x;
				ft_strncpy(&res[1], *str, len_str);
				free (*str);
				*str = res;
			}
		}
	}
}

void                    conv_di(t_lst *lst, t_chr **mychr, va_list ap)
{
	size_t          size;
	char            *str;
	char            *nbr;
	long long int	n;
	int             i;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ?
		cast_di(*(lst->arglist), lst->format->flag) : cast_di(ap, lst->format->flag);
	if (n == 0 && !lst->format->precis)
	{
		(*mychr)->str = ft_strcnew(lst->format->width, ' ');
		((*mychr)->str)[lst->format->width] = '\0';
		(*mychr)->len = lst->format->width;
		return ;
	}
	nbr = ft_lltoa(n);
	flag_apostrophe(&nbr, lst->format);
	size = ft_max(ft_strlen(nbr), lst->format->width);
	if (!(str = ft_strnew(size)))
		return ;
	if (ft_strchr(lst->format->flag, '-'))
	{
		ft_strcpy(str, nbr);
		i = ft_strlen(nbr);
		while (i < (int)size)
			str[i++] = ' ';
	}
	else
	{
		i = 0;
		while (i < (int)(size - ft_strlen(nbr) + 1))
			str[i++] = ' ';
		ft_strcpy(&str[--i], nbr);
	}
	if (lst->format->precis > 0
			&& lst->format->precis < lst->format->width)
		precis_di(&str, lst->format, ft_strlen(nbr));
	else if (lst->format->precis >= lst->format->width)
		str = all_zero_di(nbr, lst->format->precis, 0);	
	else if (ft_strchr(lst->format->flag, '0')
			&& lst->format->width > (int)ft_strlen(nbr) && !ft_strchr(lst->format->flag, '-'))
		str = all_zero_di(nbr, lst->format->width, 1);
	if (n >= 0)
	{
		if (ft_strchr(lst->format->flag, '+'))
			flag_plusp_di(lst->format, &str, (int)ft_strlen(nbr), '+');
		else if (ft_strchr(lst->format->flag, ' '))
			flag_plusp_di(lst->format, &str, (int)ft_strlen(nbr), ' ');
	}
	(*mychr)->str = str;
	free(nbr);
	(*mychr)->len = ft_strlen(str);
}
