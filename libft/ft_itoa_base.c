/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:37:16 by ishaimou          #+#    #+#             */
/*   Updated: 2019/02/08 10:17:15 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	affect_sign(int val)
{
	if (val < 0)
		return (1);
	return (0);
}

static long	affect_nb(int val)
{
	if (val < 0)
		return (-(long)val);
	return ((long)val);
}

char		*ft_itoa_base(int val, int base)
{
	long	nb;
	int	size;
	int	sign;
	char	*res;

	sign = affect_sign(val);
	size = affect_sign(val) + 1;
	nb = affect_nb(val);
	while (nb /= base)
		size++;
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return NULL;
	res[size] = '\0';
	nb = affect_nb(val);
	if (sign)
		res[0] = '-';
	while (size-- > sign)
	{
		if (nb % base < 10)
			res[size] = (nb % base) + '0';
		else
			res[size] = (nb % base) + 'A' - 10;
		nb /= base;
	}
	return (res);
}
