/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_ee.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:48:46 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/08 06:46:57 by obelouch         ###   ########.fr       */
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
 ** a[0] = len_e | a[1] = len_f | a[2] = carry | a[3] = p
 */

void		conv_ee(t_lst *lst, t_chr **mychr, t_double db)
{
	char			*final;
	char			*fract;
	char			*entier;
	int				a[4];

	a[2] = 0;
	if (pre_d_calc(db, mychr, lst))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, lst->format);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, lst->format);
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
