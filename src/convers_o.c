/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_xxoub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:35:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/08 03:45:06 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*all_zero_o(char *nbr, int precis, int dash, int width)
{
	char		*res;
	int		len;
	int		len_nbr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len_nbr = (int)ft_strlen(nbr);
	len = precis;
	if (!width && dash)
		len++;
	res = ft_strnew(len);
	if (dash)
	{
		res[i++] = '0';
		j++;
	}
	while (i < (len - len_nbr))
		res[i++] = '0';
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

	len = (ft_strchr(fmt->flag, '#')) ? (nbr_len - 1) : nbr_len;
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		nbr = ft_strdup(*str);
		if (ft_strchr(fmt->flag, '#'))
			j++;
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
		while (j-- >= 0 && i >= 0)
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
			(*mychr)->str = ft_strcnew(lst->format->width + 1, '0');
			((*mychr)->str)[lst->format->width + 1] = '\0';
			(*mychr)->len = lst->format->width + 1;
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
		if (lst->format->precis >= lst->format->width)
			str = all_zero_o(nbr, lst->format->precis, (ft_strchr(lst->format->flag, '#')) ? 1 : 0, 0);
		if (ft_strchr(lst->format->flag, '0')
				&& lst->format->width > (int)ft_strlen(nbr)
				&& !ft_strchr(lst->format->flag, '-')
				&& lst->format->precis <= 0)
			str = all_zero_o(nbr, lst->format->width, (ft_strchr(lst->format->flag, '#')) ? 1 : 0, 1);
		(*mychr)->str = str;
		free(nbr);
	}
	(*mychr)->len = ft_strlen(str);
}
