/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_ee.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:48:46 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/03 21:59:11 by obelouch         ###   ########.fr       */
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

void		conv_ee(t_lst *lst, t_chr **mychr, t_double db)
{
	char			*entier;
	char			*final;
	char			*fract;
	char			*tmp;
	unsigned int	len_e;
	unsigned int	len_f;
	unsigned int	len;
	int				carry;
	int				p;

	carry = 0;
	if (pre_d_calc(db, mychr, lst))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS, lst->format);
	if (db.d < 1 && db.d > 0)
		db.d++;
	if (db.d > -1 && db.d < 0)
		db.d--;
	printf("entier before: %s\n", entier);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS, lst->format);
	printf("\nfract before: %s\n", fract);
	ft_putchar('\n');
	p = addjust_e(&entier, &fract);
	printf("entier after addjust: %s\n", entier);
	printf("fract after addjust : %s\n", fract);
	fract = ft_fprecis(fract, lst->format->precis, &carry);
	if (carry == 1)
		entier = ft_strsum(entier, "1", 10);
	if (ft_strlen(entier) > 1)
		ft_scum(&entier, &fract, &p);
	flag_apostrophe(&fract, lst->format);
	printf("entier after*: %s\n", entier);
	printf("fract after*: %s\n", fract);
	if (db.zone.sign)
		entier = add_sign(entier, (int)(db.zone.sign));
	len_e = ft_strlen(entier);
	len_f = ft_strlen(fract);
	len = len_e + len_f + 1;
	if (lst->format->width > (int)len && !ft_strchr(lst->format->flag, '-'))
	{
		entier = ft_fwidth(entier, len_e, lst->format, len_f);
		len = lst->format->width;
	}
	if (ft_strchr(lst->format->flag, '+'))
		flag_plus(&entier, lst->format->convers);
	else if (ft_strchr(lst->format->flag, ' ') && !ft_strchr(lst->format->flag, '-'))
		flag_space(&entier, lst->format->flag);
	len_e = ft_strlen(entier);
	if (ft_strchr(lst->format->flag, '#') || lst->format->precis != 0)
		tmp = ft_strjoin(entier, ".");
	else
		tmp = ft_strjoin(entier, "");
	final = (lst->format->precis > 0) ? ft_strjoin(tmp, fract) : ft_strjoin(tmp, "");
	printf("fract  : %s\n", fract);
	final = ft_finish_e(final, p, lst->format->convers);
	free(tmp);
	free(fract);
	printf("entier: %s\n", entier);
	free(entier);
	(*mychr)->str = final;
	(*mychr)->len = len;
	printf("%.70f\n", db.d);
	printf("mantis: %llx\n", (unsigned long long int)db.zone.mantissa);
	printf("expo  : %s\n", ft_itoa_base(db.zone.exponent, 2));
	printf("sign  : %s\n", ft_itoa_base(db.zone.sign, 2));
	ft_putchar('\n');
}
