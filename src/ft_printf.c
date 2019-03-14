/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 14:46:18 by obelouch          #+#    #+#             */
/*   Updated: 2019/03/08 16:20:53 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		zero_xxob(char **str, t_format *fmt)
{
	int	i;

	i = 0;
	while ((*str)[i] == ' ')
		(*str)[i++] = '0';
	(*str)[i] = '0';
	if (fmt->convers != 'o')
		(*str)[++i] = '0';
	if (fmt->convers == 'b')
		(*str)[1] = 'b';
	else if (fmt->convers == 'x' || fmt->convers == 'X')
		(*str)[1] = 'x';
}

void		zero_dbiouxx(char **str, t_format *fmt)
{
	int		i;

	i = 0;
	if (ft_strchr("udi", fmt->convers))
	{
		while ((*str)[i] == ' ')
			(*str)[i++] = '\0';
	}
	else if (ft_strchr("xxob", fmt->convers))
		zero_xxob(str, fmt);
	else if (fmt->convers == 'p')
	{
		(*str)[i++] = '0';
		(*str)[i++] = 'x';
		while ((*str)[i] != 'x')
			(*str)[i++] = '0';
		(*str)[i] = '0';
	}
}

static void	precis_o_udi(char **str, int n_zero)
{
	int	i;

	i = -1;
	if (n_zero <= 0)
		return ;
	while ((*str)[++i] == ' ');
	while (n_zero--)
		(*str)[--i] = '0';
}

void            cast_di(va_list ap, char *flag, long long int *n)
{
	if (ft_strstr(flag, "hh"))
		*n = (char)va_arg(ap, int);
	else if (ft_strstr(flag, "h"))
		*n = (short int)va_arg(ap, int);
	else if (ft_strstr(flag, "ll"))
		*n = (long long int)va_arg(ap, long long int);
	else if (ft_strstr(flag, "l"))
		*n = (long int)va_arg(ap, long int);
	else
		*n = (int)va_arg(ap, int);
}

void		conv_di(t_lst *lst, t_chr **mychr, va_list ap)
{
	size_t		size;
	char		*str;
	char		*nbr;
	int		i;
	long long int	d;

	flag_star(lst->format, ap);
	cast_di(ap, lst->format->flag, &d);
	if (d == 0 && !lst->format->precis)
		(*mychr)->str = ft_strdup("\0");
	else
	{
		nbr = ft_itoa(d);
		if (ft_strchr(lst->format->flag, '+'))
			flag_plus(&nbr);
		if (d >= 0 && ft_strchr(lst->format->flag, ' '))
			flag_space(&nbr, lst->format->flag);
		size = (lst->format->width);
		if (lst->format->width < lst->format->precis)
			size = lst->format->precis;
		if (size <= ft_strlen(nbr) || ft_strchr(lst->format->flag, '-'))
			size = ft_strlen(nbr);
		if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
			return ;
		str[size] = '\0';
		i = -1;
		while (++i < (int)(size - ft_strlen(nbr)))
			str[i] = ' ';
		str[i] = '\0';
		if (d < 0 && ft_strchr(lst->format->flag, '0'))
		{
			nbr[0] = '0';
			str[0] = '-';
		}
		ft_strcat(str, nbr);
		if (ft_strchr(lst->format->flag, '0')
				&& lst->format->width > (int)ft_strlen(nbr)
				&& lst->format->precis == 0)
			zero_dbiouxx(&str, lst->format);
		if (lst->format->precis > 0)
			precis_o_udi(&str, lst->format->precis - ft_strlen(nbr));
		(*mychr)->str = str;
		free(nbr);
	}
	(*mychr)->len = ft_strlen(str);
}

void		conv_percent(t_chr **mychr)
{
	(*mychr)->str = ft_strdup("%");
	(*mychr)->len = 1;
}

static void	precis_zero(char **str, int n_zero)
{
	int	i;

	i = 0;
	if (n_zero > 0)
	{
		while ((*str)[i++] != 'x');
		while (n_zero--)
			(*str)[--i] = '0';
		(*str)[--i] = 'x';
		(*str)[--i] = '0';
	}
}

void		conv_p(t_lst *lst, t_chr **mychr, va_list ap)
{
	char	*str;
	char	*nbr;
	size_t	size;
	int	i;

	flag_star(lst->format, ap);
	nbr = ft_utoa_base((size_t)va_arg(ap, void*), 16);
	flag_dash(&nbr, 16);
	nbr = ft_strlowcase(nbr);
	if (ft_strchr(lst->format->flag, ' ') && lst->format->width <= (int)ft_strlen(nbr))
		flag_space(&nbr, lst->format->flag);
	size = (lst->format->width > lst->format->precis + 2) ? lst->format->width : lst->format->precis + 2;
	if (size <= ft_strlen(nbr) || ft_strchr(lst->format->flag, '-'))
		size = ft_strlen(nbr);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return ;
	str[size] = '\0';
	i = 0;
	while (i < (int)(size - ft_strlen(nbr) + 1))
		str[i++] = ' ';
	i--;
	ft_strcpy(&str[i], nbr);
	if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr))
		zero_dbiouxx(&str, lst->format);
	if (lst->format->precis > 0)
		precis_zero(&str, lst->format->precis - 12);
	(*mychr)->str = str;
	(*mychr)->len = size;
	free(nbr);
}

static int				base_detect(char c)
{
	if (c == 'x' || c == 'X')
		return (16);
	if (c == 'u')
		return (10);
	if (c == 'o')
		return (8);
	if (c == 'b')
		return (2);
	return (0);
}

void		cast_xxoub(va_list ap, char *flag, size_t *n)
{
	if (ft_strstr(flag, "hh"))
		*n = (unsigned char)va_arg(ap, unsigned int);
	else if (ft_strstr(flag, "h"))
		*n = (unsigned short int)va_arg(ap, unsigned int);
	else if (ft_strstr(flag, "ll"))
		*n = (unsigned long long int)va_arg(ap, unsigned long long int);
	else if (ft_strstr(flag, "l"))
		*n = (unsigned long int)va_arg(ap, unsigned long int);
	else
		*n = (unsigned int)va_arg(ap, unsigned int);
}

void            conv_xxoub(t_lst *lst, t_chr **mychr, va_list ap)
{
	int     prefix;
	size_t     size;
	char    *str;
	char    *nbr;
	int	i;
	size_t	n;

	flag_star(lst->format, ap);
	cast_xxoub(ap, lst->format->flag, &n);
	i = base_detect(lst->format->convers);
	prefix = (lst->format->convers == 'o') ? 1 : 2;
	nbr = ft_utoa_base(n, i);
	if (ft_strchr(lst->format->flag, '#') && lst->format->convers != 'u')
		flag_dash(&nbr, i);
	else
		prefix = 0;
	if (lst->format->precis - prefix > 0)
		nbr[lst->format->precis + prefix] = '\0';
	size = lst->format->width;
	if (lst->format->width < lst->format->precis)
		size = lst->format->precis;
	if (size <= ft_strlen(nbr) || ft_strchr(lst->format->flag, '-'))
		size = ft_strlen(nbr);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return ;
	str[size] = '\0';
	i = -1;
	while (++i < (int)(size - ft_strlen(nbr) + 1))
		str[i] = ' ';
	ft_strcpy(&str[--i], nbr);
	if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr))
		zero_xxob(&str, lst->format);
	if (lst->format->precis > 0)
		precis_o_udi(&str, lst->format->precis - ft_strlen(nbr));
	if (lst->format->convers == 'x')
		str = ft_strlowcase(str);
	if (lst->format->convers == 'X')
		str = ft_strupcase(str);
	(*mychr)->str = str;
	(*mychr)->len = ft_strlen(str);
	free(nbr);
}

void		conv_invalid(t_chr **mychr, t_format *format, va_list ap)
{
	int		i;

	flag_star(format, ap);
	i = -1;
	if (!format->width)
	{
		(*mychr)->str = ft_strnew(1);
		(*mychr)->str[0] = format->convers;
		(*mychr)->len = 1;
	}
	else
	{
		(*mychr)->str = ft_strnew(format->width);
		while (++i < format->width - 1)
			(*mychr)->str[i] = ' ';
		(*mychr)->str[i] = format->convers;
		(*mychr)->len = format->width;
	}
}

void		conv_color(t_lst *lst, t_chr **mychr, va_list ap)
{
	if (lst->format->convers != '}')
	{
		conv_invalid(mychr, lst->format, ap);
		return ;
	}
	(*mychr)->len = 0;
	if (!ft_strcmp(lst->format->flag, "red"))
		(*mychr)->str = ft_strdup(RED);
	else if (!ft_strcmp(lst->format->flag, "green"))
		(*mychr)->str = ft_strdup(GREEN);
	else if (!ft_strcmp(lst->format->flag, "yellow"))
		(*mychr)->str = ft_strdup(YELLOW);
	else if (!ft_strcmp(lst->format->flag, "blue"))
		(*mychr)->str = ft_strdup(BLUE);
	else if (!ft_strcmp(lst->format->flag, "purple"))
		(*mychr)->str = ft_strdup(PURPLE);
	else if (!ft_strcmp(lst->format->flag, "cyan"))
		(*mychr)->str = ft_strdup(CYAN);
	else if (!ft_strcmp(lst->format->flag, "eoc"))
		(*mychr)->str = ft_strdup(EOC);
	else
		conv_invalid(mychr, lst->format, ap);
}

int		ft_printf(const char *format, ...)
{
	t_chr		*mychr;
	t_lst		*lst;
	va_list		ap;
	int		len;
	int		len_format;

	len = 0;
	len_format = 0;
	while (format[len_format])
		len_format++;
	va_start(ap, format);
	lst = parse_format((char*)format);
	if (!lst)
	{
		put_spstr((char*)format);
		if (format[len_format - 1] == '%')
			return (-1);
		return (ft_strlen(format));
	}
	print_lst(lst);
	if (!(mychr = load_chr((char*)format, lst)))
		return -1;
	print_chr(mychr);
	ft_putendl((char*)format);
	fill_chr(lst, mychr, ap);
	print_lst(lst);
	show_lst(lst);
	print_chr(mychr);
	len = put_chr(mychr);
	free_lst(lst);
	free_chr(mychr);
	return (len);
}
