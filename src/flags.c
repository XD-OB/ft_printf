/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:40:38 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/04 22:14:03 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flag_plus(char **nbr, char conv)
{
	char	*str;
	int		len;

	if (ft_atoi(*nbr) > 0 || ft_strchr("puxX", conv))
	{
		len = ft_strlen(*nbr) + 1;
		str = (char*)malloc(sizeof(char) * (len + 1));
		str[0] = '+';
		str[len] = '\0';
		ft_strcpy(&str[1], *nbr);
		free(*nbr);
		*nbr = str;
	}
}

void		flag_space(char **nbr, char *flag)
{
	char	*str;
	int		len;

	if (!ft_strchr(flag, '+'))
	{
		len = ft_strlen(*nbr) + 1;
		str = (char*)malloc(sizeof(char) * (len + 1));
		if (ft_atoi(*nbr) >= 0)
			str[0] = ' ';
		str[len] = '\0';
		ft_strcpy(&str[1], *nbr);
		free(*nbr);
		*nbr = str;
	}
}

void		flag_zero(char **str, t_format *format)
{
	int		i;

	if (format->precis == 0 && !ft_strchr(format->flag, '+'))
	{
		i = -1;
		while (++i < (format->width - (int)ft_strlen(*str)))
			(*str)[i] = '0';
	}
}

void		flag_star(t_format *format, va_list ap)
{
	if (ft_strchr(format->flag, '*'))
		format->width = va_arg(ap, int);
	if (format->precis == -2)
		format->precis = (int)va_arg(ap, int);
}

int			flag_dollar(t_lst *lst)
{
	int		i;

	if (ft_strchr(lst->format->flag, '$'))
	{
		i = 0;
		while (++i < lst->format->argn)
			va_arg(*(lst->arglist), void*);
		return (1);
	}
	return (0);
}
