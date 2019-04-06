/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:38:44 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/06 03:55:25 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	len[2]:		len[0]: len_e		len[1]: len_f
*/

char		*modify_lf(t_format *fmt, char *entier, char *fract, int carry, t_double db)
{
	char			*tmp;
	char			*final;
	unsigned int	len[2];

	if (carry == 1)
		entier = (fmt->convers == 'H') ?
			ft_strsum(entier, "1", 16) : ft_strsum(entier, "1", 10);
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
	final = modify_lf(lst->format, entier, fract, carry, db);
	//free(fract);
	//free(entier);
	(*mychr)->str = final;
	(*mychr)->len = ft_strlen(final);
}
