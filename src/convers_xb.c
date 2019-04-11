/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_xb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 04:08:02 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/10 00:21:52 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*xx_zero_res(t_format *fmt, char *nbr, int len_nbr, char c)
{
	char		*res;
	int		i;
	int		j;

	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (!ft_strchr(fmt->flag, '-'))
	{
		i = fmt->width;
		j = len_nbr;
		while (--j >= 0)
			res[--i] = nbr[j];
		while (--i >= 0)
			res[i] = c;
	}
	else
	{
		i = 0;
		j = 0;
		while (j < len_nbr)
			res[i++] = nbr[j++];
		while (i < fmt->width)
			res[i++] = c;
	}
	return (res);
}

char			*xx_zero(t_format *fmt)
{
	int		len_nbr;
	char		*nbr;
	char		*res;
	char		c;

	len_nbr = fmt->precis;
	if (fmt->precis == -1)
		len_nbr = 1;
	nbr = ft_strcnew(len_nbr, '0');
	if (fmt->width > len_nbr)
	{
		c = (fmt->precis == -1 && ft_strchr(fmt->flag, '0') 
			&& !ft_strchr(fmt->flag, '-')) ? '0' : ' ';
		res = xx_zero_res(fmt, nbr, len_nbr, c);
		free(nbr);
		return (res);
	}
	return (nbr);
}

static char		*xx_n(t_format *fmt, char *num, int len_num, int base)
{
	int		len_nbr;
	int		is_dash;
	int		diff;
	char		*res;
	char		*nbr;
	char		c;
	int		i;
	int		j;

	len_num = ft_strlen(num);
	is_dash = (ft_strchr(fmt->flag, '#')) ? 2 : 0;
	len_nbr = ft_max(len_num, fmt->precis) + is_dash;
	nbr = (char*)malloc(sizeof(char) * (len_nbr + 1));
	nbr[len_nbr] = '\0';
	i = len_nbr;
	j = len_num;
	while (--j >= 0)
		nbr[--i] = num[j];
	while (--i >= 0)
		nbr[i] = '0';
	diff = fmt->width - len_nbr;
	if (is_dash)
	{
		nbr[0] = '0';
		nbr[1] = (base == 16) ? 'x' : 'b';
	}
	if (diff > 0)
	{
		c = (fmt->precis == -1 && ft_strchr(fmt->flag, '0') 
			&& !ft_strchr(fmt->flag, '-')) ? '0' : ' ';
		res = (char*)malloc(sizeof(char) * (fmt->width + 1));
		res[fmt->width] = '\0';
		if (!ft_strchr(fmt->flag, '-'))
		{
			i = -1;
			while (++i < diff)
				res[i] = c;
			if (is_dash && c == '0')
			{
				res[1] = (base == 16) ? 'x' : 'b';
				nbr[1] = '0';
			}
			j = -1;
			while (++j < len_nbr)
				res[i++] = nbr[j];
		}
		else
		{
			i = 0;
			j = 0;
			while (j < len_nbr)
				res[i++] = nbr[j++];
			while (i < fmt->width)
				res[i++] = ' ';
		}
		free(nbr);
		return (res);
	}
	return (nbr);
}

void                    conv_xx(t_lst *lst, t_chr **chr, va_list ap)
{
	unsigned long long int	n;
	char			*num;
	char			*res;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format)
				: cast_xxoub(ap, lst->format);
	if (n == 0)
		res = xx_zero(lst->format);
	else
	{
		num = ft_ulltoa_base(n, 16);
		res = xx_n(lst->format, num, (int)ft_strlen(num), 16);
		free(num);
	}
	(lst->format->convers == 'x') ? res = ft_strlowcase(res) : 0;
	(lst->format->convers == 'X') ? res = ft_strupcase(res) : 0;
	(*chr)->str = res;
	(*chr)->len = (int)ft_strlen(res);
}

void                    conv_b(t_lst *lst, t_chr **chr, va_list ap)
{
	unsigned long long int	n;
	char			*num;
	char			*res;
	
	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format)
				: cast_xxoub(ap, lst->format);
	if (n == 0)
		res = xx_zero(lst->format);
	else
	{
		num = ft_itoa_base(n, 2);
		res = xx_n(lst->format, num, (int)ft_strlen(num), 2);
		free(num);
	}
	(lst->format->convers == 'b') ? ft_strlowcase(res) : 0;
	(lst->format->convers == 'B') ? ft_strupcase(res) : 0;
	(*chr)->str = res;
	(*chr)->len = (int)ft_strlen(res);
}
