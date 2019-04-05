/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_xxoub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:35:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/05 07:19:05 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		base_detect(char c)
{
	if (c == 'u')
		return (10);
	if (c == 'o')
		return (8);
	if (c == 'b')
		return (2);
	return (0);
}

static size_t	cast_xxoub(va_list ap, char *flag)
{
	size_t		n;

	if (ft_strstr(flag, "hh"))
		n = (unsigned char)va_arg(ap, unsigned int);
	else if (ft_strstr(flag, "h"))
		n = (unsigned short int)va_arg(ap, unsigned int);
	else if (ft_strstr(flag, "ll"))
		n = (unsigned long long int)va_arg(ap, unsigned long long int);
	else if (ft_strstr(flag, "l"))
		n = (unsigned long int)va_arg(ap, unsigned long int);
	else
		n = (unsigned int)va_arg(ap, unsigned int);
	return (n);
}

static char		*fill_oub_str(t_format *fmt, char *nbr, size_t size_nbr)
{
	size_t		size;
	char		*str;
	size_t		i;

	size = (fmt->width > fmt->precis) ? fmt->width : fmt->precis;
	(size < size_nbr) ? size = size_nbr : 0;
	if (!(str = ft_strnew(size)))
		return (0);
	if (ft_strchr(fmt->flag, '-'))
	{
		ft_strcpy(str, nbr);
		i = size_nbr;
		while (i < size)
			str[i++] = ' ';
	}
	else
	{
		i = 0;
		while (i < (size - size_nbr + 1))
			str[i++] = ' ';
		ft_strcpy(&str[--i], nbr);
		if (ft_strchr(fmt->flag, '0') && fmt->width > (int)(size_nbr)
				&& fmt->precis == -1)
			zero_dbiou(&str, fmt);
		if (fmt->precis >= fmt->width)
			zero_dbiou(&str, fmt);
	}
	return (str);
}

void			precis_x(char **str, t_format *fmt, size_t nbr_len)
{
	int		i;
	int		j;
	int		len;
	char	*nbr;

	len = (ft_strchr(fmt->flag, '#')) ? (nbr_len - 2) : nbr_len;
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		nbr = ft_strdup(*str);
		if (ft_strchr(fmt->flag, '#'))
		{
			j = 2;
			(*str)[i++] = '0';
			(*str)[i++] = 'X';
		}
		while (i < fmt->precis - len)
			(*str)[i++] = '0';
		while(j < len)
			(*str)[i++] = nbr[j++];
		free(nbr);
	}
	else
	{
		i = ft_strlen(*str) - len - 1;
		j = fmt->precis - len;
		while (j-- && i >= 0)
			(*str)[i--] = '0';
		if (ft_strchr(fmt->flag, '#'))
		{
			(*str)[i--] = 'X';
			(*str)[i] = '0';
		}
	}
}

char			*all_zero_x(char *nbr, int precis, int dash, int width)
{
	char	*res;
	int		len;
	int		len_nbr;
	int		i;
	int		j;

	len_nbr = (int)ft_strlen(nbr);
	len = precis;
	if (dash && !width)
		len += 2;
	res = ft_strnew(len);
	i = 0;
	j =  0;
	if (dash)
	{
		len_nbr -= 2;
		res[i++] = '0';
		res[i++] = 'x';
		j = 2;
	}
	while (i < (len - len_nbr))
		res[i++] = '0';
	while (i < len)
		res[i++] = nbr[j++];
	return (res);
}

void			conv_ub(t_lst *lst, t_chr **mychr, va_list ap)
{
	char		*str;
	char		*nbr;
	size_t		n;
	int			i;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format->flag)
		: cast_xxoub(ap, lst->format->flag);
	if (n == 0 && !lst->format->precis)
		(*mychr)->str = ft_strnew(0);
	else
	{
		i = base_detect(lst->format->convers);
		nbr = ft_utoa_base(n, i);
		ft_putstr("\nnbr = ");
		ft_putstr(nbr);
		ft_putstr("\n");
		if (n && ft_strchr(lst->format->flag, '#')
				&& lst->format->convers != 'u')
			flag_dash(&nbr, i);
		ft_putstr("\nnbr aftre dash  = ");
		ft_putstr(nbr);
		ft_putstr("\n");
		flag_apostrophe(&nbr, lst->format);
		str = fill_oub_str(lst->format, nbr, ft_strlen(nbr));
		ft_putstr("\nstr = ");
		ft_putstr(str);
		ft_putstr("\n");
		if (lst->format->precis > 0 && lst->format->precis < lst->format->width)
				precis_o_udi(&str, lst->format, ft_strlen(nbr));
		ft_putstr("\nstr precis_ox= ");
		ft_putstr(str);
		ft_putstr("\n");
		//if (lst->format->precis > 0 && lst->format->convers == 'u')
		//	precis_o_udi(&str, lst->format, ft_strlen(nbr));
		(*mychr)->str = str;
		free(nbr);
	}
	(*mychr)->len = ft_strlen(str);
}

char			*all_zero_o(char *nbr, int precis, int dash, int width)
{
	char	*res;
	int		len;
	int		len_nbr;
	int		i;
	int		j;

	len_nbr = (int)ft_strlen(nbr);
	len = precis;
	if (dash && !width)
		len++;
	res = ft_strnew(len);
	i = 0;
	j =  0;
	if (dash)
	{
		len_nbr--;
		res[i++] = '0';
		j++;
	}
	while (i < (len - len_nbr))
		res[i++] = '0';
	while (j < len_nbr)
		res[i++] = nbr[j++];
	return (res);
}

void			precis_o(char **str, t_format *fmt, size_t nbr_len)
{
	int		i;
	int		j;
	int		len;
	char	*nbr;

	len = (ft_strchr(fmt->flag, '#')) ? (nbr_len - 2) : nbr_len;
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		nbr = ft_strdup(*str);
		if (ft_strchr(fmt->flag, '#'))
			j++;
		while (i < fmt->precis - len)
			(*str)[i++] = '0';
		while(j < len)
			(*str)[i++] = nbr[j++];
		free(nbr);
	}
	else
	{
		i = ft_strlen(*str) - len - 1;
		j = fmt->precis - len;
		while (j-- && i >= 0)
			(*str)[i--] = '0';
	}
}

void			conv_o(t_lst *lst, t_chr **mychr, va_list ap)
{
	size_t		size;
	char		*str;
	char		*nbr;
	size_t		n;
	int			i;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format->flag)
		: cast_xxoub(ap, lst->format->flag);
	if (n == 0 && !lst->format->precis)
		(*mychr)->str = ft_strnew(0);
	else
	{
		nbr = ft_utoa_base(n, 8);
		if (n && ft_strchr(lst->format->flag, '#'))
			flag_dash(&nbr, 8);
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
		ft_putstr("\nstr = ");
		ft_putendl(str);
		if (lst->format->precis > 0 && lst->format->precis < lst->format->width)
				precis_o(&str, lst->format, ft_strlen(nbr));
		if (lst->format->precis >= lst->format->width)
			str = all_zero_o(nbr, lst->format->precis, (ft_strchr(lst->format->flag, '#')) ? 1 : 0, 0);
		if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr))
			str = all_zero_o(nbr, lst->format->width, (ft_strchr(lst->format->flag, '#')) ? 1 : 0, 1);
		(*mychr)->str = str;
		free(nbr);
	}
	(*mychr)->len = ft_strlen(str);
}

void			conv_xx(t_lst *lst, t_chr **mychr, va_list ap)
{
	size_t		size;
	char		*str;
	char		*nbr;
	size_t		n;
	int			i;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format->flag)
		: cast_xxoub(ap, lst->format->flag);
	if (n == 0 && !lst->format->precis)
		(*mychr)->str = ft_strnew(0);
	else
	{
		nbr = ft_utoa_base(n, 16);
		if (n && ft_strchr(lst->format->flag, '#'))
			flag_dash(&nbr, 16);
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
		ft_putstr("\nstr = ");
		ft_putendl(str);
		if (lst->format->precis > 0 && lst->format->precis < lst->format->width)
				precis_x(&str, lst->format, ft_strlen(nbr));
		if (lst->format->precis >= lst->format->width)
			str = all_zero_x(nbr, lst->format->precis, (ft_strchr(lst->format->flag, '#')) ? 1 : 0, 0);
		if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr))
			str = all_zero_x(nbr, lst->format->width, (ft_strchr(lst->format->flag, '#')) ? 1 : 0, 1);
		(lst->format->convers == 'x') ? str = ft_strlowcase(str) : 0;
		(lst->format->convers == 'X') ? str = ft_strupcase(str) : 0;
		(*mychr)->str = str;
		free(nbr);
	}
	(*mychr)->len = ft_strlen(str);
}
