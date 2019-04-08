/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   date.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 02:48:52 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/03 04:55:11 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void				date_conv(long int s, long int *y, unsigned int *date)
{
	int					era;
	long int			nbr_days;
	unsigned int		ey[4];

	nbr_days = s / 86400 + 719468;
	if (nbr_days < 0)
		era = (nbr_days - 146096) / 146097;
	era = (int)(nbr_days / 146097);
	ey[0] = (unsigned int)(nbr_days - era * 146097);
	ey[2] = (ey[0] - ey[0] / 1460 + ey[0] / 36524 - ey[0] / 146096) / 365;
	*y = (int)ey[2] + era * 400;
	ey[1] = ey[0] - (365 * ey[2] + ey[2] / 4 - ey[2] / 100);
	ey[3] = (5 * ey[1] + 2) / 153;
	date[1] = ey[1] - (153 * ey[3] + 2) / 5 + 1;
	if (ey[3] < 10)
		date[0] = ey[3] + 3;
	else
		date[0] = ey[3] - 9;
	*y += (date[0] <= 2);
	date[2] = (s / 3600) - ((*y - 1970) * 8766) - (date[0] - 1) * 730.5
		- (date[1] - 1) * 24;
	date[3] = (s / 60) - ((*y - 1970) * 525960) - (date[0] - 1) * 43830
		- (date[1] - 1) * 1440 - date[2] * 60;
	date[4] = s - ((*y - 1970) * 31557600) - (date[0] - 1) * 2629800
		- (date[1] - 1) * 86400 - date[2] * 3600 - date[3] * 60;
}

static unsigned int		fill_times(long int y, char **times, int size,
											unsigned int *date)
{
	int					i;
	unsigned int		len;

	i = 0;
	len = 0;
	times[0] = ft_utoa(y);
	times[1] = ft_utoa(date[0]);
	times[2] = ft_utoa(date[1]);
	times[3] = ft_utoa(date[2]);
	times[4] = ft_utoa(date[3]);
	times[5] = ft_utoa(date[4]);
	while (i < size)
		len += ft_strlen(times[i++]);
	return (len);
}

static char				*c_date(char **times, int len)
{
	char				*res;

	len -= ft_strlen(times[5]) - ft_strlen(times[4]) - ft_strlen(times[3]);
	res = (char*)malloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	ft_strcat(res, times[0]);
	ft_strcat(res, "-");
	ft_strcat(res, times[1]);
	ft_strcat(res, "-");
	ft_strcat(res, times[2]);
	return (res);
}

static char				*e_date(char **times, int len)
{
	char				*res;

	res = (char*)malloc(sizeof(char) * len + 1);
	res[len] = '\0';
	ft_strcat(res, times[0]);
	ft_strcat(res, "/");
	ft_strcat(res, times[1]);
	ft_strcat(res, "/");
	ft_strcat(res, times[2]);
	ft_strcat(res, " ");
	ft_strcat(res, times[3]);
	ft_strcat(res, ":");
	ft_strcat(res, times[4]);
	ft_strcat(res, ":");
	ft_strcat(res, times[5]);
	return (res);
}

/*
**	var:		var[0] : s		var[1] : y		var[2] : i
*/

void				conv_k(t_format *format, t_chr **mychr, va_list ap)
{
	long int		var[3];
	unsigned int		date[5];
	char			*res;
	char			*times[6];
	unsigned int		len;

	var[0] = (long int)va_arg(ap, long int);
	date_conv(var[0], &var[1], date);
	len = fill_times(var[1], times, 6, date);
	if (ft_strchr(format->flag, '0'))
		res = c_date(times, len);
	else
		res = e_date(times, len + 5);
	(*mychr)->str = res;
	(*mychr)->len = ft_strlen(res);
	var[2] = -1;
	while (++var[2] < 6)
		free(times[var[2]]);
}
