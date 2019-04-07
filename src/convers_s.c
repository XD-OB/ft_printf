/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 03:21:07 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/07 03:15:15 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		test_null(t_lst *lst, char *str, t_chr **chr)
{
	if (!str)
	{
		(*chr)->str = (lst->format->precis != -1) ? ft_strndup("(null)", lst->format->precis) : ft_strdup("(null)");
		(*chr)->len = ft_strlen((*chr)->str);
		return (1);
	}
	return (0);
}

static void		conv_s_annex1(t_lst *lst, int *len, char **str, t_chr **mychr)
{
	int			i;
	int			j;

	i = 0;
	if (len[0] > (int)ft_strlen(str[0]))
		len[0] = (int)ft_strlen(str[0]);
	while (i < len[1] - len[0])
		str[1][i++] = (ft_strchr(lst->format->flag, '0')) ? '0' : ' ';
	j = -1;
	while ((++j + len[1] - len[0]) < len[1])
	{
		if (ft_isprint(str[0][j]) || !ft_strchr(lst->format->flag, 'r'))
			str[1][i] = str[0][j];
		else
		{
			ft_strcat(&(str[1][i]), flag_r(str[0][j]));
			i += 4;
		}
		i++;
	}
	(*mychr)->str = str[1];
}

static void		conv_s_annex2(t_lst *lst, int *len, char **str, t_chr **mychr)
{
	int			i;
	int			j;

	if (len[0] > (int)ft_strlen(str[0]))
		len[0] = (int)ft_strlen(str[0]);
	i = 0;
	j = -1;
	while (++j < len[0])
	{
		if (ft_isprint(str[0][j]) || !ft_strchr(lst->format->flag, 'r'))
			str[1][i] = str[0][j];
		else
		{
			ft_strcat(&(str[1][i]), flag_r(str[0][j]));
			i += 4;
		}
		i++;
	}
	while (j++ < len[1])
		str[1][i++] = ' ';
	(*mychr)->str = str[1];
}

static void		conv_s_annex(t_lst *lst, int *len, char **str, t_chr **mychr)
{
	int			i;

	if (!ft_strpbrk(lst->format->flag, "-+"))
		conv_s_annex1(lst, len, str, mychr);
	else if (ft_strchr(lst->format->flag, '-')
			&& lst->format->width > lst->format->precis)
		conv_s_annex2(lst, len, str, mychr);
	else
	{
		i = -1;
		while (++i < len[0])
			str[1][i] = str[0][i];
		(*mychr)->str = str[1];
	}
}

void			conv_s(t_lst *lst, t_chr **mychr, va_list ap)
{
	int			count_np;
	int			len[2];
	char		*str[2];

	flag_star(lst->format, ap);
	if (flag_dollar(lst))
		(*mychr)->str = ft_dollar_cs(lst->format);
	else
	{
		str[0] = va_arg(ap, char*);
		if (test_null(lst, str[0], mychr))
			return ;
		len[0] = (lst->format->precis != -1) ? lst->format->precis
			: (int)ft_strlen(str[0]);
		len[1] = lst->format->width;
		count_np = ft_countnp(str[0]);
		if (!(str[1] = ft_strnew(len[1] + (count_np * 4))))
			return ;
		conv_s_annex(lst, len, str, mychr);
	}
	(*mychr)->len = ft_strlen((*mychr)->str);
}
