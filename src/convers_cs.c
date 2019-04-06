/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_cs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 03:21:07 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/05 22:41:59 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_dollar_cs(t_format *fmt)
{
	char		*tmp;
	char		*str;

	str = (fmt->argn > 0) ? ft_itoa(fmt->argn) : ft_strnew(0);
	tmp = ft_strjoin("$", str);
	free(str);
	str = ft_strjoin(tmp, &(fmt->convers));
	free(tmp);
	return (str);
}

void			conv_c(t_lst *lst, t_chr **mychr, va_list ap)
{
	int			i;
	int			len;
	char		*str;

	flag_star(lst->format, ap);
	if (flag_dollar(lst))
	{
		(*mychr)->str = ft_dollar_cs(lst->format);
		(*mychr)->len = ft_strlen((*mychr)->str);
		return ;
	}
	len  = (lst->format->width < 2) ? 1 : lst->format->width;
	str = ft_strnew(len);
	if (ft_strchr(lst->format->flag, '-'))
	{
		i = 0;
		str[i] = (char)va_arg(ap, int);
		while (++i < len)
			str[i] = ' ';
	}
	else
	{
		i = -1;
		while (++i < len - 1)
			str[i] = (ft_strchr(lst->format->flag, '0') ? '0' : ' ');
		str[i] = (char)va_arg(ap, unsigned int);
	}
	(*mychr)->str = str;
	(*mychr)->len = len;
}

static int		ft_countnp(char *s)
{
	int			count_np;
	int			i;

	i = -1;
	count_np = 0;
	while (s[++i])
	{
		if ((s[i] >= 0 && s[i] < 32) || s[i] == 127)
			count_np++;
	}
	return (count_np);
}

static int		test_null(char *str, t_chr **chr)
{
	if (!str)
	{
		(*chr)->str = ft_strdup("(null)");
		(*chr)->len = 6;
		return (1);
	}
	return (0);
}

void			conv_s(t_lst *lst, t_chr **mychr, va_list ap)
{
	int			count_np;
	int			len[2];
	char		*str[2];
	int			i;
	int			j;

	flag_star(lst->format, ap);
	if (flag_dollar(lst))
		(*mychr)->str = ft_dollar_cs(lst->format);
	else
	{
		str[0] = va_arg(ap, char*);
		if (test_null(str[0], mychr))
			return ;
		len[0] = (lst->format->precis != -1) ? lst->format->precis
											: (int)ft_strlen(str[0]);
		len[1] = lst->format->width;
		count_np = ft_countnp(str[0]);
		if (!(str[1] = ft_strnew(len[1] + (count_np * 4))))
			return ;
		i = 0;
		if (!ft_strpbrk(lst->format->flag, "-+"))
		{
			if (len[0] > (int)strlen(str[0]))
				len[0] = (int)strlen(str[0]);
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
		else if (ft_strchr(lst->format->flag, '-') && lst->format->width > lst->format->precis)
		{
			if (len[0] > (int)strlen(str[0]))
				len[0] = (int)strlen(str[0]);
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
		else
		{
			i = -1;
			while (++i < len[0])
				str[1][i] = str[0][i];
			(*mychr)->str = str[1];
		}
	}
	(*mychr)->len = ft_strlen((*mychr)->str);
}
