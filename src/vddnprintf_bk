/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vddnprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 03:27:29 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/03 04:07:15 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** len:		len[0] : len		len[1] : len_format
*/

int			ft_vprintf(const char *format, va_list ap)
{
	t_chr	*mychr;
	t_lst	*lst;
	int		len[2];

	len[0] = 0;
	len[1] = 0;
	while (format[len[1]])
		len[1]++;
	lst = parse_format(ap, (char*)format);
	if (!lst)
	{
		put_spstr((char*)format);
		return ((format[len[1] - 1] == '%') ? -1 : (int)ft_strlen(format));
	}
	if (!(mychr = load_chr((char*)format, lst)))
		return (-1);
	fill_chr(lst, mychr, ap);
	len[0] = put_chr(mychr);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len[0]);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	t_chr	*mychr;
	t_lst	*lst;
	va_list	ap;
	int		len[2];

	len[0] = 0;
	len[1] = -1;
	while (format[len[1]])
		len[1]++;
	va_start(ap, format);
	lst = parse_format(ap, (char*)format);
	if (!lst)
	{
		put_spstr((char*)format);
		return ((format[len[1] - 1] == '%') ? -1 : (int)ft_strlen(format));
	}
	if (!(mychr = load_chr((char*)format, lst)))
		return (-1);
	fill_chr(lst, mychr, ap);
	len[0] = put_chr_fd(fd, mychr);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len[0]);
}

int			ft_dnprintf(int fd, size_t n, const char *format, ...)
{
	t_chr	*mychr;
	t_lst	*lst;
	va_list	ap;
	int		len[2];

	len[0] = 0;
	len[1] = 0;
	while (format[len[1]])
		len[1]++;
	va_start(ap, format);
	lst = parse_format(ap, (char*)format);
	if (!lst)
	{
		put_spstr((char*)format);
		return ((format[len[1] - 1] == '%') ? -1 : (int)ft_strlen(format));
	}
	if (!(mychr = load_chr((char*)format, lst)))
		return (-1);
	fill_chr(lst, mychr, ap);
	len[0] = put_chr_nfd(fd, n, mychr);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len[0]);
}
