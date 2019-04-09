/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_xxoub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:35:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/10 00:21:45 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*all_zero_o(t_format *fmt, char *nbr, int precis, int dash)
{
	char		*res;
	int		len;
	int		len_nbr;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	len_nbr = (int)ft_strlen(nbr);
	c = (!fmt->precis && fmt->precis <  len_nbr) ? ' ' : '0';
	len = ft_max(precis, len_nbr);
	if (dash)
		len++;
	res = ft_strnew(len);
	while (i < (len - len_nbr))
		res[i++] = c;
	if (dash)
	{
		res[i - 1] = '0';
		j++;
	}
	while (i < len)
		res[i++] = nbr[j++];
	return (res);
}

void			precis_o(char **str, t_format *fmt, size_t nbr_len)
{
	int		i;
	int		j;
	int		len;
	char	*nbr;

	len = (ft_strchr(fmt->flag, '#') && nbr_len > 1) ? (nbr_len - 1) : nbr_len;
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		nbr = ft_strdup(*str);
		//if (ft_strchr(fmt->flag, '#') && ft_strchr(fmt->flag, '0'))
		//	j++;
		while (i < fmt->precis - len)
			(*str)[i++] = '0';
		while(j < (int)nbr_len)
			(*str)[i++] = nbr[j++];
		free(nbr);
	}
	else
	{
		i = ft_strlen(*str) - len - 1;
		j = fmt->precis - len;
		while (j-- > 0 && i >= 0)
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
	char		c;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format)
		: cast_xxoub(ap, lst->format);
	if (n == 0 && !lst->format->precis)
	{
		if (!ft_strchr(lst->format->flag, '#'))
		{
			(*mychr)->str = ft_strcnew(lst->format->width, ' ');
			((*mychr)->str)[lst->format->width] = '\0';
			(*mychr)->len = lst->format->width;
		}
		else
		{
			if (!lst->format->width)
				lst->format->width++;
			c = (ft_strchr(lst->format->flag, '0')
					&& lst->format->precis == -1) ? '0' : ' ';
			(*mychr)->str = ft_strcnew(lst->format->width, c);
			((*mychr)->str)[lst->format->width] = '\0';
			if (ft_strchr(lst->format->flag, '-'))
				((*mychr)->str)[0] = '0';
			else
				((*mychr)->str)[lst->format->width - 1] = '0';
			(*mychr)->len = lst->format->width;
		}
		return ;
	}
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
		if (!ft_strchr(lst->format->flag, '0') && lst->format->precis > 0
						&& lst->format->precis < lst->format->width)
				precis_o(&str, lst->format, ft_strlen(nbr));
		else if (lst->format->precis >= lst->format->width)
			str = all_zero_o(lst->format, nbr, lst->format->precis, (ft_strchr(lst->format->flag, '#')) ? 1 : 0);
		else if (ft_strchr(lst->format->flag, '0')
				&& lst->format->width > (int)ft_strlen(nbr)
				&& !ft_strchr(lst->format->flag, '-')
				&& lst->format->precis <= 0)
		{
			str = all_zero_o(lst->format, nbr, lst->format->width, (ft_strchr(lst->format->flag, '#')) ? 1 : 0);
		}
		else
		{
			size = ft_strlen(nbr);
			c = (ft_strchr(lst->format->flag, '0')) ? '0' : ' ';
			if (lst->format->width > (int)size)
			{
				if (!ft_strchr(lst->format->flag, '-'))
				{
					i = lst->format->width - lst->format->precis - 1;
					while (++i < lst->format->width - (int)size)
						str[i] = c;
				}
				else
				{
					i = (int)size - 1;
					while (++i < lst->format->precis)
						str[i] = c;
				}
			}
		}
		(*mychr)->str = str;
		free(nbr);
	}
	(*mychr)->len = ft_strlen(str);
}
