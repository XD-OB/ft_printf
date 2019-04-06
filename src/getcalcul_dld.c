/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcalcul_dld.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:02:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/06 01:21:44 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char            *calcul_entierd(char *tab, int size, t_format *format)
{
	char		*entier;
	char		*count;
	unsigned int	len;
	int 		debut;
	int 		i;
	int		base;

	base = (format->convers == 'H') ? 16 : 10;
	entier = ft_strdup("0");
	count = ft_strdup("1");
	len =  1;
	debut = -1;
	while(tab[++debut] == '0');
	i = size;
	while (--i >= debut)
	{
		if (tab[i] == '1')
		{
			entier = ft_strsum(entier, count, base);
			len = ft_strlen(entier);
		}
		count = ft_strmult("2", count, base);
		len++;
	}
	entier[len] = '\0';
	return (entier);
}

char		*calcul_fractd(char *bat, int size, t_format *format)
{
	char		*fract;
	int		i;
	char		*count;
	unsigned int	len;
	int		base;

	i = -1;
	base = (format->convers == 'H') ? 16 : 10;
	fract = ft_strdup("0");
	len = 1;
	count = ft_strdup("5");
	while (bat[--size] == '0');
	while (++i <= size)
	{
		ft_putchar(bat[i]);
		if (bat[i] == '1')
		{
			fract = ft_strsum(fract, count, base);
			len = ft_strlen(fract);
		}
		count = ft_strmult("5", count, base);
		fract = foisdix(fract, len);
		len++;
	}
	return (fract);
}

char		*get_entierd(long exp, long bin_mantis, int bias, t_format *format)
{
	unsigned long long int		m;
	long				new_exp;
	char				*tab;
	int				size_dec;
	int				i;

	tab = NULL;
	size_dec = 0;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	if (new_exp < 0)
		return (ft_strdup("0"));
	m = (bias == D_BIAS) ? 2251799813685248 : 2305843000000000000;
	if (bias == D_BIAS)
	{
		tab = (exp) ? int_addone(tab, size_dec, 1) : int_addone(tab, size_dec, 0);
		size_dec++;
	}
	i = -1;
	while (++i < new_exp)
	{
		tab = (m & bin_mantis) ? int_addone(tab, size_dec, 1) : int_addone(tab, size_dec, 0);
		size_dec++;
		m >>= 1;
	}
	return (calcul_entierd(tab, size_dec, format));
}

char		*get_fractd(long exp, long bin_mantis, int bias, t_format *format)
{
	int			len_b;
	unsigned int		size;
	char			*bat;
	long			new_exp;

	bat = NULL;
	size = 0;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	len_b = (bias = D_BIAS) ? ABS(52 - new_exp - 1) : ABS(63 - new_exp - 1);
	while (len_b >= 0)
	{
		if (new_exp < -1)
		{
			bat = int_addone(bat, size, 0);
			size++;
			new_exp++;
		}
		else if (new_exp == -1)
		{
			bat = int_addone(bat, size, 1);
			size++;
			new_exp++;
		}
		else
		{
			bat = ((bin_mantis >> len_b) & 1) ?
				int_addone(bat, size, 1) : int_addone(bat, size, 0);
			size++;
		}
		len_b--;
	}
	return  (calcul_fractd(bat, size, format));
}