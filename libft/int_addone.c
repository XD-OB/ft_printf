/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_addone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:28:01 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/06 00:28:45 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*int_addone(char *tab, int oldsize, int data)
{
	char	*new;
	int		i;

	i = -1;
	new = ft_strnew(oldsize + 1);
	while (++i < oldsize)
		new[i] = tab[i];
	new[i] = data + '0';
	if (oldsize)
		free(tab);
	return (new);
}
