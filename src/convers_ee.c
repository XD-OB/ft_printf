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
**	len[3]:		i => 0		len_e = 1		len_f = 2
**	new[2]:		new_entier => 0		new_fract => 1
*/

static int	addjust_e(char **entier, char **fract)
{
	char	*new[2];
	int		len[3];

	len[1] = ft_strlen(*entier);
	if ((*entier)[0] != '0' && len[1] == 1)
		return (0);
	len[2] = ft_strlen(*fract);
	if (len[1] > 1)
	{
		new[0] = ft_strcnew(1, (*entier)[0]);
		new[1] = ft_strjoin(&(*entier)[1], *fract);
	}
	else
	{
		len[0] = 0;
		while ((*fract)[len[0]] == '0')
			(len[0])++;
		new[0] = ft_strcnew(1, (*fract)[len[0]]);
		new[1] = ft_strdup(&(*fract)[++len[0]]);
	}
	ft_strswap(entier, &(new[0]));
	ft_strswap(fract, &(new[1]));
	free(new[0]);
	free(new[1]);
	return ((len[1] > 1) ? (len[1] - 1) : ((int)ft_strlen(*fract) - len[2]));
}

static void	ft_scum(char **entier, char **fract, int *p)
{
	char	*new_entier;
	char	*new_fract;

	new_entier = ft_strcnew(1, *entier[0]);
	new_fract = ft_strnjoin(*fract, "", ft_strlen(*fract) - 1);
	ft_strswap(entier, &new_entier);
	ft_strswap(fract, &new_fract);
	free(new_entier);
	free(new_fract);
	(*p)++;
}

static char	*ft_finish_e(char *final, int p, char c)
{
	char	*new_final;
	char	*tmp;
	char	*tmp_tmp;
	char	*sc_e;

	tmp = ft_utoa(ABS(p));
	if (p > 9)
		sc_e = ft_strjoin("e+", tmp);
	else if (p < -9)
		sc_e = ft_strjoin("e-", tmp);
	else
	{
		tmp_tmp = ft_strjoin("0", tmp);
		sc_e = (p >= 0) ? ft_strjoin("e+", tmp_tmp) : ft_strjoin("e-", tmp_tmp);
		free(tmp_tmp);
	}
	new_final = ft_strjoin(final, sc_e);
	(c == 'E') ? ft_strupcase(new_final) : 0;
	free(tmp);
	free(final);
	return (new_final);
}

void		reduce_fract(char **str)
{
	unsigned int	len;

	len = ft_strlen(*str) - 1;
	while ((*str)[len] == '0')
		len--;
	(*str)[len + 1] = '\0';
}

char		*final_ee(t_format *fmt, char **entier, char *fract, int *a)
{
	char		*final;
	char		*tmp;

	if (fmt->width > (a[0] + a[1] + 1) && !ft_strchr(fmt->flag, '-'))
		*entier = ft_fwidth(*entier, a[0], fmt, a[1]);
	if (ft_strchr(fmt->flag, '+'))
		flag_plus(entier, fmt->convers);
	else if (ft_strchr(fmt->flag, ' ') && !ft_strchr(fmt->flag, '-'))
		flag_space(entier, fmt->flag);
	a[0] = ft_strlen(*entier);
	tmp = (ft_strchr(fmt->flag, '#') || fmt->precis != 0) ?
		ft_strjoin(*entier, ".") : ft_strjoin(*entier, "");
	(ft_strchr("gG", fmt->convers)) ? reduce_fract(&fract) : 0;
	final = (fmt->precis > 0) ? ft_strjoin(tmp, fract) : ft_strjoin(tmp, "");
	final = ft_finish_e(final, a[3], fmt->convers);
	free(tmp);
	free(*entier);
	free(fract);
	return (final);
}

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
	len[3] = ft_strlen(num_e);
	prefix = ft_strjoin(sc_e, num_e);
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
	str = ft_strjoin(entier, ".");
	tmp = ft_strjoin(str, fract);
	free(str);
	str = ft_strjoin(tmp, prefix);
	free(prefix);
	free(tmp);
	len[3] += (len[3] == 1) ? 3 : 2;
	len[3] += len[0] + len[1] + 1;
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
	(lst->format->width > (int)len) ? customize_f(lst->format, &str, &((*chr)->len), db.zone.sign)
					: add_sign_f(lst->format, &str, &((*chr)->len), db.zone.sign);
	free(entier);
	free(fract);	
	(*chr)->str = str;
}


void		conv_lee(t_lst *lst, t_chr **mychr, va_list ap)
{
	char			*final;
	char			*fract;
	char			*entier;
	int				a[4];
	t_ldouble		db;

	a[2] = 0;
	flag_star(lst->format, ap);
	db.ld = (flag_dollar(lst)) ? va_arg(*(lst->arglist), long double) : va_arg(ap, long double);
	(lst->format->precis == -1) ? lst->format->precis = 6 : 0;
	if (pre_ld_calc(db, mychr, lst))
		return ;
	entier = get_entierld(int_exp(db.zone.exponent, LD_BIAS), db, lst->format);
	fract = get_fractld(int_exp(db.zone.exponent, LD_BIAS), db, lst->format);
	a[3] = addjust_e(&entier, &fract);
	(ft_strchr("gG", lst->format->convers)) ? lst->format->precis-- : 0;
	if (lst->format->precis > 0)
		fract = ft_fprecis(fract, lst->format->precis, a + 2);
	(a[2] == 1) ? entier = ft_strsum(entier, "1", 10) : 0;
	(ft_strlen(entier) > 1) ? ft_scum(&entier, &fract, a + 3) : 0;
	flag_apostrophe(&fract, lst->format);
	(db.zone.sign) ? entier = add_sign(entier, (int)(db.zone.sign)) : 0;
	a[0] = ft_strlen(entier);
	a[1] = ft_strlen(fract);
	final = final_ee(lst->format, &entier, fract, a);
	(*mychr)->str = final;
	(*mychr)->len = ft_strlen(final);
}
