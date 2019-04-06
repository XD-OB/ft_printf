/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_dld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:11:52 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/06 01:23:49 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_fprecis(char *fract, int precis, int *carry)
{
	char		*str;
	char		*tmp;
	int		len;
	int		i;

	str = ft_strnew(precis);
	len = ft_strlen(fract);
	i = -1;
	if (precis > len)
	{
		while (++i < len)
			str[i] = fract[i];
		while (i < precis)
			str[i++] = '0';
	}
	else
	{
		while (++i < precis)
			str[i] = fract[i];
		if (fract[i] > '4')
		{
			tmp = ft_strsum(str, "1", 10);
			if (ft_strlen(tmp) > (unsigned int)precis)
			{
				i = -1;
				while (str[++i])
					str[i] = '0';
				*carry = 1;
			}
			else
				ft_strswap(&tmp, &str);
			free(tmp);
		}
	}
	free(fract);
	return (str);
}

char		*ft_fwidth(char *str, unsigned int size_str, t_format *format, unsigned int len_f)
{
	unsigned int	i;
	unsigned int	len;
	char			*res;
	char			c;

	c = (ft_strchr(format->flag, '0')) ? '0' : ' ';
	len = format->width - len_f;
	if (ft_strchr(format->flag, '+'))
		len++;
	if (format->precis != 0 || ft_strchr(format->flag, '#'))
		len--;
	if (ft_strpbrk(format->flag, "#+")
			|| (ft_strchr(format->flag, ' ') && !ft_strchr(format->flag, '-')))
		len--;
	res = ft_strnew(len);
	i = 0;
	while (i < len - size_str)
		res[i++] = c;
	i--;
	while (++i < len)
		res[i] = str[i - (len - size_str)];
	free(str);
	return (res);
}

char		*ft_fwidthf(char *str, unsigned int size_str, t_format *format, unsigned int len_e)
{
	unsigned int	i;
	unsigned int	len;
	char			*res;
	char			c;

	c = (ft_strchr(format->flag, '0')) ? '0' : ' ';
	len = format->width - len_e;
	if (format->precis != 0 || ft_strchr(format->flag, '#'))
		len--;
	if (ft_strpbrk(format->flag, "#+")
			|| (ft_strchr(format->flag, ' ') && !ft_strchr(format->flag, '-')))
		len--;
	res = ft_strnew(len);
	i = 0;
	while (i < size_str)
	{
		res[i] = str[i];
		i++;
	}
	i--;
	while (++i < len)
		res[i] = c;
	free(str);
	return (res);
}

char		*add_sign(char *str, int sign)
{
	char		*res;
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(str) + 1;
	res = ft_strnew(len);
	res[0] = (sign) ? '-' : '+';
	i = 0;
	while (++i < len)
		res[i] = str[i - 1];
	free(str);
	return (res);
}
