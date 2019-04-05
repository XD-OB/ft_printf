/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_pcolinv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:20:38 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/05 05:24:43 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		precis_zero(char **str, int n_zero)
{
	int			i;

	i = 0;
	if (n_zero > 0)
	{
		while ((*str)[i] != 'x')
			i++;
		while (n_zero--)
			(*str)[--i] = '0';
		(*str)[--i] = 'x';
		(*str)[--i] = '0';
	}
}

static char		*fill_p_str(char *nbr, size_t nbr_size, t_format *fmt)
{
	char		*str;
	size_t		size;
	size_t		i;

	i = 0;
	size = (fmt->width > (fmt->precis + 2)) ? fmt->width : fmt->precis + 2;
	(size < nbr_size) ? size = nbr_size : 0;
	if (!(str = ft_strnew(size)))
		return (0);
	if (!ft_strchr(fmt->flag, '-'))
	{
		while (i < (size - nbr_size + 1))
			str[i++] = ' ';
		ft_strcpy(&str[--i], nbr);
	}
	else
	{
		ft_strcpy(str, nbr);
		i = ft_strlen(str) - 1;
		while (++i < size)
			str[i] = ' ';
	}
	return (str);
}

void			conv_p(t_lst *lst, t_chr **mychr, va_list ap)
{
	char		*str;
	char		*nbr;
	size_t		size_nbr;

	flag_star(lst->format, ap);
	if (flag_dollar(lst))
		nbr = ft_utoa_base((size_t)va_arg(*(lst->arglist), void*), 16);
	else
		nbr = ft_utoa_base((size_t)va_arg(ap, void*), 16);
	flag_dash(&nbr, 16);
	if (ft_strchr(lst->format->flag, '+'))
		flag_plus(&nbr, lst->format->convers);
	nbr = ft_strlowcase(nbr);
	size_nbr = ft_strlen(nbr);
	if (ft_strchr(lst->format->flag, ' ')
			&& lst->format->width <= (int)size_nbr)
		flag_space(&nbr, lst->format->flag);
	str = fill_p_str(nbr, size_nbr, lst->format);
	if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)size_nbr)
		zero_dbiou(&str, lst->format);
	if (lst->format->precis > 0)
		precis_zero(&str, lst->format->precis - 12);
	(*mychr)->str = str;
	(*mychr)->len = (int)ft_strlen(str);
	free(nbr);
}

void			conv_invalid(t_chr **mychr, t_format *format, va_list ap)
{
	int			i;

	flag_star(format, ap);
	i = -1;
	if (!format->width)
	{
		(*mychr)->str = ft_strnew(1);
		(*mychr)->str[0] = format->convers;
		(*mychr)->len = 1;
	}
	else
	{
		(*mychr)->str = ft_strnew(format->width);
		while (++i < format->width - 1)
			(*mychr)->str[i] = ' ';
		(*mychr)->str[i] = format->convers;
		(*mychr)->len = format->width;
	}
}

void			conv_color(t_lst *lst, t_chr **mychr)
{
	(*mychr)->len = 0;
	if (!ft_strcmp(lst->format->flag, "red"))
		(*mychr)->str = ft_strdup(RED);
	else if (!ft_strcmp(lst->format->flag, "green"))
		(*mychr)->str = ft_strdup(GREEN);
	else if (!ft_strcmp(lst->format->flag, "yellow"))
		(*mychr)->str = ft_strdup(YELLOW);
	else if (!ft_strcmp(lst->format->flag, "blue"))
		(*mychr)->str = ft_strdup(BLUE);
	else if (!ft_strcmp(lst->format->flag, "purple"))
		(*mychr)->str = ft_strdup(PURPLE);
	else if (!ft_strcmp(lst->format->flag, "cyan"))
		(*mychr)->str = ft_strdup(CYAN);
	else if (!ft_strcmp(lst->format->flag, "eoc"))
		(*mychr)->str = ft_strdup(EOC);
	else
	{
		(*mychr)->str = ft_strdup(lst->format->flag);
		(*mychr)->len = ft_strlen((*mychr)->str);
	}
}
