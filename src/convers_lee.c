/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_lee.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 03:59:42 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/07 02:47:27 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static char		*get_entierld(long exp, t_ldouble db, t_format *format)
{
	long	new_exp;
	long	bin_mantis;
	char	*tab;
	int		size_dec;
	int		i;

	tab = NULL;
	size_dec = 0;
	bin_mantis = db.zone.mantissa;
	new_exp = (exp == 0) ? 1 - LD_BIAS : exp - LD_BIAS;
	if (new_exp < 0)
		return (ft_strdup("0"));
	tab = (db.zone.int_b) ? int_addone(tab, size_dec, 1) : int_addone(tab, size_dec, 0);
	size_dec++;
	i = 62;
	while (new_exp > 0)
	{
		tab = (1 & (bin_mantis >> i)) ? int_addone(tab, size_dec, 1) : int_addone(tab, size_dec, 0);
		size_dec++;
		i--;
		new_exp--;
	}
	i = -1;
	while (++i < size_dec)
		ft_putchar(tab[i]);
	ft_putchar('\n');
	return (calcul_entier(tab, size_dec, format));
}

static char		*get_fractld(long exp, t_ldouble db, t_format *format)
{
	int			len_b;
	unsigned int		size;
	char			*tab;
	long			new_exp;
	long			bin_mantis;

	tab = NULL;
	size = 0;
	new_exp = (exp == 0) ? 1 - LD_BIAS : exp - LD_BIAS;
	bin_mantis = db.zone.mantissa;
	len_b = ABS(63 - new_exp - 1);
	if (len_b < 0)
		return (ft_strdup("0"));
	while (len_b >= 0)
	{
		if (new_exp < -1)
		{
			tab = int_addone(tab, size, 0);
			size++;
			new_exp++;
		}
		else if (new_exp == -1)
		{
			tab = (db.zone.int_b) ? int_addone(tab, size, 1) : int_addone(tab, size, 0);
			size++;
			new_exp++;
		}
		else
		{
			tab = ((bin_mantis >> len_b) & 1) ?
				int_addone(tab, size, 1) : int_addone(tab, size, 0);
			size++;
		}
		len_b--;
	}
	return  (calcul_fract(tab, size, format));
}


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

char		*final_lee(t_format *fmt, char **entier, char *fract, int *a)
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
	if (ft_strchr(fmt->flag, '#') || fmt->precis != 0)
		tmp = ft_strjoin(*entier, ".");
	else
		tmp = ft_strjoin(*entier, "");
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
	fract = ft_fprecis(fract, lst->format->precis, a + 2);
	(a[2] == 1) ? entier = ft_strsum(entier, "1", 10) : 0;
	(ft_strlen(entier) > 1) ? ft_scum(&entier, &fract, a + 3) : 0;
	flag_apostrophe(&fract, lst->format);
	(db.zone.sign) ? entier = add_sign(entier, (int)(db.zone.sign)) : 0;
	a[0] = ft_strlen(entier);
	a[1] = ft_strlen(fract);
	final = final_lee(lst->format, &entier, fract, a);
	(*mychr)->str = final;
	(*mychr)->len = ft_strlen(final);
}
