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

char	*ft_btoa(unsigned char octet)
{
	unsigned char	tmp;
	char		*res;
	int		i;
	int		j;
	int		len;

	j = 0;
	i = 1;
	len = 0;
	tmp = octet;
	while (tmp)
	{
		tmp >>= 1;
		len++;
	}
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return NULL;
	res[len] = '\0';
	while (len--)
		i *= 2;
	while (i >>= 1)
	{
		if (!(octet & i))
			res[j] = '0';
		else
			res[j] = '1';
		j++;
	}
	return (res);
}
