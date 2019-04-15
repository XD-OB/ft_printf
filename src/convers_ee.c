/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_ee.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:48:46 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/15 18:19:32 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	new[2]:		new[0]: new_entier	new[1]: new_fract
** 	len[3]:	len[0]: len_e	len[1]: len_f	len[2]: pos   len[3]: len
*/

static void	fix_esize(char **str, int len_s, int size)
{
	char	*res;
	int	i;

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

void		eprecis(char **str, int precis, int *carry, int *len_s)
{
	char	*fract;
	char	*tmp;

	if (precis == 0)
	{
		if ((*str)[0] > '4')
			*carry = 1;
		fract = ft_strnew(0);
	}
	else
	{
		if (precis > *len_s)
			fix_esize(str, *len_s, precis + 2);
		fract = ft_strndup(*str, precis);
		*len_s = precis;
		if ((*str)[precis] > '4')
		{
			tmp = ft_strsum(fract, "1", 10);
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

static int	addjust_ee(char **entier, char **fract, int *len)
{
	char	*new[2];
	int	i;
	int	p;

	if ((*entier)[0] != '0' && len[0] == 1)
		return (0);
	len[1] = ft_strlen(*fract);
	if (len[0] > 1)
	{
		new[0] = ft_strcnew(1, (*entier)[0]);
		new[1] = ft_strjoin(&(*entier)[1], *fract);
	}
	else
	{
		i = 0;
		while ((*fract)[i] == '0')
			i++;
		new[0] = ft_strcnew(1, (*fract)[i]);
		new[1] = ft_strdup(&(*fract)[++i]);
	}
	ft_strswap(entier, &(new[0]));
	ft_strswap(fract, &(new[1]));
	free(new[0]);
	free(new[1]);
	i = ft_strlen(*fract);
	p = (len[0] > 1) ? (len[0] - 1) : (i - len[1]);
	len[0] = 1;
	len[1] = i;
	return (p);
}

char		*eprefix(t_format *fmt, int *len)
{
	char	*prefix;
	char	*sc_e;
	char	*num_e;

	if (len[2] >= 0 && len[2] < 10)
		sc_e = ft_strdup("e+0");
	else if (len[2] > 9)
		sc_e = ft_strdup("e+");
	else if (len[2] < -9)
		sc_e = ft_strdup("e-");
	else
		sc_e = ft_strdup("e-0");
	if (fmt->convers == 'E')
		ft_strupcase(sc_e);
	num_e = ft_utoa(ABS(len[2]));
	prefix = ft_strjoin(sc_e, num_e);
	len[3] = ft_strlen(prefix);
	free(num_e);
	free(sc_e);
	return (prefix);
}

char		*ejoin(t_format *fmt, char *entier, char *fract, int *len)
{
	char	*prefix;
	char	*tmp;
	char	*str;

	prefix = eprefix(fmt, len);
	len[3] += len[0];
	if (ft_strcmp(fract, "\0") || ft_strchr(fmt->flag, '#'))
	{
		str = ft_strjoin(entier, ".");
		len[3]++;
	}
	else
		str = ft_strdup(entier);
	if (ft_strcmp(fract, "\0"))
	{
		tmp = ft_strjoin(str, fract);
		len[3] += len[1];
		free(str);
	}
	else
		tmp = str;
	str = ft_strjoin(tmp, prefix);
	free(prefix);
	free(tmp);
	return (str);
}

void		conv_ee(t_lst *lst, t_chr **chr, t_double db)
{
	char	*entier;
	char	*fract;
	char	*str;
	int	len[4];
	int	carry;

	carry = 0;
	if (pre_d_calc(db, chr, lst))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, lst->format);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, lst->format);
	len[0] = ft_strlen(entier);
	len[1] = ft_strlen(fract);
	len[2] = addjust_ee(&entier, &fract, len);
	eprecis(&fract, lst->format->precis, &carry, &len[1]);
	if (carry == 1)
	{
		str = entier;
		entier = ft_strsum(str, "1", 10);
		free(str);
	}
	str = ejoin(lst->format, entier, fract, len);
	(*chr)->len = len[3];
	(lst->format->width > len[3]) ? customize_f(lst->format, &str, &((*chr)->len), db.zone.sign)
					: add_sign_f(lst->format, &str, &((*chr)->len), db.zone.sign);
	free(entier);
	free(fract);	
	(*chr)->str = str;
}


void		conv_lee(t_lst *lst, t_chr **chr, va_list ap)
{
	t_ldouble		db;
	char	*entier;
	char	*fract;
	char	*str;
	int	len[4];
	int	carry;

	carry = 0;
	flag_star(lst->format, ap);
	db.ld = (flag_dollar(lst)) ? va_arg(*(lst->arglist), long double) : va_arg(ap, long double);
	(lst->format->precis == -1) ? lst->format->precis = 6 : 0;
	if (pre_ld_calc(db, chr, lst))
		return ;
	entier = get_entierld(int_exp(db.zone.exponent, LD_BIAS), db, lst->format);
	fract = get_fractld(int_exp(db.zone.exponent, LD_BIAS), db, lst->format);
	(ft_strchr("gG", lst->format->convers)) ? lst->format->precis-- : 0;
	len[0] = ft_strlen(entier);
	len[1] = ft_strlen(fract);
	len[2] = addjust_ee(&entier, &fract, len);
	eprecis(&fract, lst->format->precis, &carry, &len[1]);
	if (carry == 1)
	{
		str = entier;
		entier = ft_strsum(str, "1", 10);
		free(str);
	}
	str = ejoin(lst->format, entier, fract, len);
	(*chr)->len = len[3];
	(lst->format->width > (int)len) ? customize_f(lst->format, &str, &((*chr)->len), db.zone.sign)
					: add_sign_f(lst->format, &str, &((*chr)->len), db.zone.sign);
	free(entier);
	free(fract);	
	(*chr)->str = str;
}
