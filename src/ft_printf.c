/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 14:46:18 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/08 07:01:00 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_chr		*mychr;
	t_lst		*lst;
	va_list		ap;
	int		len;
	int		len_format;
	int		pflag;

	pflag = 0;
	len = 0;
	len_format = 0;
	while (format[len_format])
		len_format++;
	va_start(ap, format);
	lst = parse_format(ap, (char*)format, &pflag);
	if (!lst)
	{
		if (pflag == -1)
			return (0);
		put_spstr((char*)format);
		if (format[len_format - 1] == '%')
			return (-1);
		return (ft_strlen(format));
	}
	//print_lst(lst);
	if (!(mychr = load_chr((char*)format, lst)))
	{
		free_lst(&lst);
		return (-1);
	}
	//print_chr(mychr);
	//ft_putendl((char*)format);
	fill_chr(lst, mychr, ap);
	//show_lst(lst);
	//print_chr(mychr);
	len = put_chr(mychr);
	free_lst(&lst);
	free_chr(&mychr);
	va_end(ap);
	return (len);
}
