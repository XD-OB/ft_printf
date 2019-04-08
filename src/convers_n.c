/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 06:57:19 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/08 07:07:55 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		conv_n(t_lst *lst, t_chr **mychr, t_chr *debut, va_list ap)
{
	int			*n;
	int			len;

	(void)lst;
	len = 0;
	n = (int*)va_arg(ap, int*);
	while (debut)
	{
		len += debut->len;
		debut = debut->next;
	}
	(*mychr)->str = ft_strnew(0);
	(*mychr)->len = 0;
	*n = len;
}
