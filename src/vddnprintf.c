/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vddnprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 03:27:29 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 07:42:36 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** len:		0: len		1: len_format		2: pflag
*/

int			ft_vprintf(const char *format, va_list ap)
{
	t_chr	*mychr;
	t_lst	*lst;
	int		len[3];

	len[0] = 0;
	len[1] = 0;
	len[2] = 0;
	while (format[len[1]])
		len[1]++;
	lst = parse_format(ap, (char*)format, &(len[2]));
	if (!lst)
	{
		if (len[2] == -1)
			return (0);
		put_spstr((char*)format);
		return ((format[len[1] - 1] == '%') ? -1 : (int)ft_strlen(format));
	}
	if (!(mychr = load_chr((char*)format, lst)))
		return (-1);
	fill_chr(lst, mychr, ap);
	len[0] = put_chr(mychr);
	free_lst(&lst);
	free_chr(&mychr);
	va_end(ap);
	return (len[0]);
}

static int	dprintf_null(char *format, int *len)
{
	if (len[2] == -1)
		return (0);
	put_spstr((char*)format);
	return ((format[len[1] - 1] == '%') ? -1 : (int)ft_strlen(format));
}

int			ft_dprintf(int fd, const char *format, ...)
{
	t_chr	*mychr;
	t_lst	*lst;
	va_list	ap;
	int		len[3];

	len[0] = 0;
	len[1] = -1;
	len[2] = 0;
	while (format[len[1]])
		len[1]++;
	va_start(ap, format);
	lst = parse_format(ap, (char*)format, &(len[2]));
	if (!lst)
		return (dprintf_null((char*)format, len));
	if (!(mychr = load_chr((char*)format, lst)))
		return (-1);
	fill_chr(lst, mychr, ap);
	len[0] = put_chr_fd(fd, mychr);
	free_lst(&lst);
	free_chr(&mychr);
	va_end(ap);
	return (len[0]);
}

static int	dprintf_null_n(char *format, int *len, size_t n)
{
	if (len[2] == -1)
		return (0);
	put_spstrn((char*)format, n);
	return ((format[len[1] - 1] == '%') ? -1 : n);
}

int			ft_dnprintf(int fd, size_t n, const char *format, ...)
{
	t_chr	*mychr;
	t_lst	*lst;
	va_list	ap;
	int		len[3];

	len[0] = 0;
	len[1] = 0;
	len[2] = 0;
	while (format[len[1]])
		len[1]++;
	va_start(ap, format);
	lst = parse_format(ap, (char*)format, &(len[2]));
	if (!lst)
		return (dprintf_null_n((char*)format, len, n));
	if (!(mychr = load_chr((char*)format, lst)))
		return (-1);
	fill_chr(lst, mychr, ap);
	len[0] = put_chr_nfd(fd, n, mychr);
	free_lst(&lst);
	free_chr(&mychr);
	va_end(ap);
	return (len[0]);
}
