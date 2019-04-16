/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:38:44 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/15 16:29:22 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_entier(long exp, long bin_mantis, int bias, t_format *format)
{
	unsigned long long int	m;
	long					new_exp;
	char					*tab;
	char					*res;
	unsigned int			size;
	int						i;

	i = -1;
	tab = NULL;
	size = 0;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	if (new_exp < 0)
		return (ft_strdup("0"));
	m = 2251799813685248;
	tab = (exp) ? int_add(tab, &size, 1) : int_add(tab, &size, 0);
	while (++i < new_exp)
	{
		tab = (m & bin_mantis) ? int_add(tab, &size, 1) : int_add(tab, &size, 0);
		m >>= 1;
	}
	res = calcul_entier(tab, size, format);
	free(tab);
	return (res);
}

char		*get_fract(long exp, long bin_mantis, int bias, t_format *format)
{
	int				len_b;
	unsigned int	size;
	char			*tab;
	char			*res;
	long			new_exp;

	tab = NULL;
	size = 0;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	len_b = ABS(52 - new_exp - 1);
	if (len_b < 0)
		return (ft_strdup("0"));
	while (len_b >= 0)
	{
		if (new_exp < -1)
		{
			tab = int_add(tab, &size, 0);
			new_exp++;
		}
		else if (new_exp == -1)
		{
			tab = (exp) ? int_add(tab, &size, 1) : int_add(tab, &size, 0);
			new_exp++;
		}
		else
			tab = ((bin_mantis >> len_b) & 1) ? int_add(tab, &size, 1) : int_add(tab, &size, 0);
		len_b--;
	}
	res = calcul_fract(tab, size, format);
	free(tab);
	return (res);
}

static void	fix_fsize(char **str, long len_s, long size)
{
	char	*res;
	long	i;

	res = (char*)malloc(sizeof(char) * (size + 1));
	res[size] = '\0';
	i = 0;
	while (i < len_s)
	{
		res[i] = (*str)[i];
		i++;
	}
	while (i < size)
		res[i++] = '0';
	free(*str);
	*str = res;
}

void		fprecis(char **str, long precis, int *carry, int base)
{
	char	*fract;
	char	*tmp;
	long	len_s;

	if (precis == 0)
	{
		if ((*str)[0] > '4')
			*carry = 1;
		fract = ft_strnew(0);
	}
	else
	{
		len_s = ft_strlen(*str);
		if (precis > len_s)
			fix_fsize(str, len_s, precis + 2);
		fract = ft_strndup(*str, precis);
		if ((*str)[precis] > '4')
		{
			tmp = ft_strsum(fract, "1", base);
			free(fract);
			if ((int)ft_strlen(tmp) > precis)
			{
				fract = ft_strsub(tmp, 1, precis);
				free(tmp);
				*carry = 1;
			}
			else
				fract = tmp;
		}
	}
	free(*str);
	*str = fract;
}

void		customize_f(t_format *fmt, char **str, unsigned int *len, int sign)
{
	unsigned int	i;
	unsigned int	j;
	char		*res;

	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		if (sign)
			res[i++] = '-';
		else if (ft_strchr(fmt->flag, '+'))
			res[i++] = '+';
		else if (ft_strchr(fmt->flag, ' '))
			res[i++] = ' ';
		while (j < *len)
			res[i++] = (*str)[j++];
		*len = fmt->width;
		while (i < *len)
			res[i++] = ' ';
	}
	else
	{
		i = fmt->width;
		j = *len;
		if (ft_strchr(fmt->flag, '0'))
		{
			while (j > 0)
				res[--i] = (*str)[--j];
			while (i > 0)
				res[--i] = '0';
			if (sign)
				res[0] = '-';
			else if (ft_strchr(fmt->flag, '+'))
				res[0] = '+';
			else if (ft_strchr(fmt->flag, ' '))
				res[0] = ' ';
		}
		else
		{
			while (j > 0)
				res[--i] = (*str)[--j];
			if (sign)
				res[--i] = '-';
			else if (ft_strchr(fmt->flag, '+'))
				res[--i] = '+';
			else if (ft_strchr(fmt->flag, ' '))
				res[--i] = ' ';
			while (i > 0)
				res[--i] = ' ';
		}
		*len = fmt->width;
	}
	free(*str);
	*str = res;
}

void		add_sign_f(t_format *fmt, char **str, unsigned int *len, int sign)
{
	unsigned int	i;
	char		*res;

	if (ft_strpbrk(fmt->flag, "+ ") || sign)
	{
		(*len)++;
		res = (char*)malloc(sizeof(char) * (*len + 1));
		res[*len] = '\0';
		if (sign)
			res[0] = '-';
		else
			res[0] = (ft_strchr(fmt->flag, '+')) ? '+' : ' ';
		i = 0;
		while (++i < *len)
			res[i] = (*str)[i - 1];
		free(*str);
		*str = res;
	}
}

void		conv_lfh(t_lst *lst, t_chr **chr, t_double db, int is_g)
{
	unsigned int	len;
	char		*fract;
	char		*entier;
	char		*str;
	char		*tmp;
	int		carry;
	int		base;

	carry = 0;
	base = (lst->format->convers == 'H') ? 16 : 10;
	if (pre_d_calc(db, chr, lst, is_g))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS, lst->format);
	(base == 16) ? flag_dash(&entier, 16) : 0;
	flag_apostrophe(&entier, lst->format);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS, lst->format);
	if (is_g)
		lst->format->precis =  ft_max((lst->format->precis - ft_strlen(entier)), 1);
	fprecis(&fract, lst->format->precis, &carry, base);
	if (carry == 1)
	{
		tmp = entier;
		entier = ft_strsum(tmp, "1", base);
		free(tmp);
	}
	str = ft_pointjoin(lst->format, entier, fract, &len);
	(lst->format->width > (int)len) ? customize_f(lst->format, &str, &len, db.zone.sign)
					: add_sign_f(lst->format, &str, &len, db.zone.sign);
	free(entier);
	free(fract);
	(*chr)->str = str;
	(*chr)->len = len;
}
