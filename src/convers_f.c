/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:38:44 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/08 23:02:27 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_entier(long exp, long bin_mantis, int bias, t_format *format)
{
	unsigned long long int	m;
	long					new_exp;
	char					*tab;
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
	return (calcul_entier(tab, size, format));
}

char		*get_fract(long exp, long bin_mantis, int bias, t_format *format)
{
	int				len_b;
	unsigned int	size;
	char			*tab;
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
			tab = (exp) ? int_add(tab, &size, 1) : int_add(tab, &size, 1);
			new_exp++;
		}
		else
			tab = ((bin_mantis >> len_b) & 1) ? int_add(tab, &size, 1) : int_add(tab, &size, 0);
		len_b--;
	}
	return  (calcul_fract(tab, size, format));
}

/*
 **	len[2]:		len[0]: len_e		len[1]: len_f
 */

static char		*modify_lf(t_format *fmt, char *entier, char *fract, t_double db)
{
	char			*tmp;
	char			*final;
	unsigned int	len[2];

	
	if (db.zone.sign || ft_strchr(fmt->flag, '+'))
		entier = add_sign(entier, (int)db.zone.sign);
	len[0] = ft_strlen(entier);
	len[1] = ft_strlen(fract);
	if (fmt->width > (int)(len[0] + len[1] + 1))
	{
		(!ft_strchr(fmt->flag, '-')) ?
			(entier = ft_fwidth(entier, len[0], fmt, len[1])) :
			(fract = ft_fwidthf(fract, len[1], fmt, len[0]));
	}
	else if (ft_strchr(fmt->flag, ' ') && !ft_strchr(fmt->flag, '-'))
		flag_space(&entier, fmt->flag);
	tmp = (ft_strchr(fmt->flag, '#') || fmt->precis != 0) ?
		ft_strjoin(entier, ".") : ft_strdup(entier);
	final = (fmt->precis > 0) ? ft_strjoin(tmp, fract) : ft_strdup(tmp);
	free(tmp);
	return (final);
}

void		conv_lfh(t_lst *lst, t_chr **mychr, t_double db)
{
	char				*fract;
	char				*entier;
	char				*final;
	int					carry;

	carry = 0;
	if (pre_d_calc(db, mychr, lst))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS, lst->format);
	if (lst->format->convers == 'H')
		flag_dash(&entier, 16);
	flag_apostrophe(&entier, lst->format);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS, lst->format);
	fract = ft_fprecis(fract, lst->format->precis, &carry);
	if (carry == 1)
		entier = (lst->format->convers == 'H') ?
			ft_strsum(entier, "1", 16) : ft_strsum(entier, "1", 10);
	final = modify_lf(lst->format, entier, fract, db);
	free(fract);
	free(entier);
	(*mychr)->str = final;
	(*mychr)->len = ft_strlen(final);
}
