/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcalcul_dld.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:02:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/12 04:21:00 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char            *calcul_entier(char *tab, int size, t_format *format)
{
	char		*entier;
	char		*count;
	int 		debut;
	int 		i;
	int		base;

	base = (format->convers == 'H') ? 16 : 10;
	entier = ft_strdup("0");
	count = ft_strdup("1");
	debut = 0;
	while(tab[debut] == '0')
		debut++;
	i = size;
	while (--i >= debut)
	{
		if (tab[i] == '1')
			entier = ft_strsum(entier, count, base);
		count = ft_strmult("2", count, base);
	}
	free(count);
	return (entier);
}

static unsigned int	ft_strupdatelen(char *str, unsigned int old)
{
	unsigned int	len;

	len = old;
	while (str[len])
		len++;
	return (len);
}

char		*calcul_fract(char *tab, int size, t_format *format)
{
	char		*fract;
	char		*count;
	unsigned int	len;
	int		base;
	int		i;

	i = -1;
	base = (format->convers == 'H') ? 16 : 10;
	fract = ft_strdup("0");
	len = 1;
	count = ft_strdup("5");
	while (tab[--size] == '0');
	while (++i <= size)
	{
		if (tab[i] == '1')
		{
			fract = ft_strsum(fract, count, base);
			len = ft_strupdatelen(fract, len);
		}
		count = ft_strmult("5", count, base);
		fract = foisdix(fract, len);
		len++;
	}
	free(count);
	return (fract);
}
