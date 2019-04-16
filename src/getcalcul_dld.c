/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcalcul_dld.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:02:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/15 17:50:41 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char            *calcul_entier(char *tab, int size, t_format *format)
{
	char		*entier;
	char		*count;
	int 		debut;
	int		base;
	int 		i;

	base = (format->convers == 'H') ? 16 : 10;
	entier = ft_strdup("0");
	debut = 0;
	while(tab[debut] == '0')
		debut++;
	i = size - 1;
	while (i >= debut && tab[i] == '0')
		i--;
	count = ft_strpower(2, (size - i - 1));
	while (i >= debut)
	{
		if (tab[i] == '1')
			sumstr(&entier, count, base);
		multstr(&count, "2", base);
		i--;
	}
	free(count);
	return (entier);
}

static int	ft_strupdatelen(char *str, int old)
{
	int	len;

	len = old;
	while (str[len])
		len++;
	return (len);
}

/*
**	var[3]: 	0: i	1: base	   2: len
*/

char		*calcul_fract(char *tab, int size, t_format *fmt)
{
	char		*fract;
	char		*count;
	int		var[3];

	var[0] = 0;
	var[2] = 1;
	var[1] = (fmt->convers == 'H') ? 16 : 10;
	while (tab[--size] == '0');
	while (var[0] <= size && tab[var[0]] == '0')
		(var[0])++;
	count = ft_strpower(5, var[0] + 1);
	fract = ft_strcnew(var[0] + 1, '0');
	while (var[0] <= size)
	{
		if (tab[var[0]] == '1')
		{
			sumstr(&fract, count, var[1]);
			var[2] = ft_strupdatelen(fract, var[2]);
		}
		multstr(&count, "5", var[1]);
		foisdix(&fract, &(var[2]));
		(var[0])++;
	}
	free(count);
	return (fract);
}
