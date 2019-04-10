/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_o_prec_zero.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:49:34 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/10 03:32:20 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*all_zero_o(t_format *fmt, char *nbr, int precis, int dash)
{
	char		*res;
	int			len;
	int			len_nbr;
	int			i[2];
	char		c;

	i[0] = 0;
	i[1] = 0;
	len_nbr = (int)ft_strlen(nbr);
	c = (!fmt->precis && fmt->precis < len_nbr) ? ' ' : '0';
	len = ft_max(precis, len_nbr);
	if (dash)
		len++;
	res = ft_strnew(len);
	while (i[0] < (len - len_nbr))
		res[i[0]++] = c;
	if (dash)
	{
		res[i[0] - 1] = '0';
		i[1]++;
	}
	while (i[0] < len)
		res[i[0]++] = nbr[i[1]++];
	return (res);
}

void			precis_o(char **str, t_format *fmt, size_t nbr_len)
{
	int			i;
	int			j;
	int			len;
	char		*nbr;

	len = (ft_strchr(fmt->flag, '#') && nbr_len > 1) ? (nbr_len - 1) : nbr_len;
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		nbr = ft_strdup(*str);
		while (i < fmt->precis - len)
			(*str)[i++] = '0';
		while (j < (int)nbr_len)
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
