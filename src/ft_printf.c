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
#include <stdio.h>

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
	if (flag_dollar(lst))
		cast_di(*(lst->arglist), lst->format->flag, &d);
	else
		cast_di(ap, lst->format->flag, &d);
	if (d == 0 && !lst->format->precis)
		(*mychr)->str = ft_strdup("\0");
	else
	{
		nbr = ft_itoa(d);
		flag_apostrophe(&nbr, lst->format);
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
	if (flag_dollar(lst))
		nbr = ft_utoa_base((size_t)va_arg(*(lst->arglist), void*), 16);
	else
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
	if (flag_dollar(lst))
		cast_xxoub(*(lst->arglist), lst->format->flag, &n);
	else
		cast_xxoub(ap, lst->format->flag, &n);
	i = base_detect(lst->format->convers);
	prefix = (lst->format->convers == 'o') ? 1 : 2;
	nbr = ft_utoa_base(n, i);
	if (ft_strchr(lst->format->flag, '#') && lst->format->convers != 'u')
		flag_dash(&nbr, i);
	else
		prefix = 0;
	flag_apostrophe(&nbr, lst->format);
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

long		int_exp(long bin_exp, int bias)
{
	long	ref;
	long	int_exp;

	int_exp = 0;
	if (bias == D_BIAS)
		ref = 2048;
	else
		ref = 32768;
	while (ref >>= 1)
		int_exp += (bin_exp & ref);
	return (int_exp);
}

long		int_mants(long bin_mants, int bias)
{
	long	ref;
	long	int_mants;

	int_mants = 0;
	if (bias == D_BIAS)
		ref = 4503599627370496;
	else
		ref = 4611686018427388000;
	while (ref)
	{
		int_mants += (bin_mants & ref);
		ref >>= 1;
	}
	return (int_mants);
}

char				*int_addone(char *tab, int oldsize, int data)
{
	char		*new;
	int		i;

	i = -1;
	new = (char*)malloc(sizeof(char) * (oldsize + 1));
	while (++i < oldsize)
		new[i] = tab[i];
	new[i] = data + '0';
	if (oldsize)
		free(tab);
	return (new);
}

unsigned long		calc_tab(char *tab, int size)
{
	long		decimal;
	int		i;

	i = -1;
	ft_putstr("size tab: ");
	ft_putnbr(size);
	ft_putchar('\n');
	decimal = 0;
	i = -1;
	while (++i < size)
	{
		ft_putstr("dank dank: ");
		ft_putchar(tab[i]);
		ft_putchar('\n');
		decimal = (decimal << 1) | (tab[i] - 48);
		printf("\ndecimal: %ld\n", decimal);
	}
	return (decimal);
}

unsigned long long		calc_bat(char *bat, int size)
{
	unsigned long long	fract;
	int			i;
	int			count;

	i = -1;
	fract = 0;
	count = 5;
	while (bat[--size] == '0');
	while (++i <= size)
	{
		ft_putchar(bat[i]);
		fract *= 10;
		if (bat[i] == '1')
			fract += count;
		printf("\nfract: %lld\n", fract);
		count *= 5;
	}
	ft_putchar('\n');
	return (fract);
}

unsigned long long int		get_decimal(long exp, long bin_mantis, int bias, unsigned long *decimal)
{
	int				i;
	long long			m;
	long				new_exp;
	char				*tab;
	char				*bat;
	int				size_dec;
	int				size;
	//long long			fract;

	tab = NULL;
	bat = NULL;
	size = 0;
	size_dec = 0;
	if (exp == 0)
		new_exp = 1 - bias;
	else
		new_exp = exp - bias;
	if (new_exp < 0)
		return (0);
	if (exp != 0)
	{
		ft_putstr("OUI\n");
		tab = int_addone(tab, size_dec, 1);
		size_dec++;
	}
	if (bias == D_BIAS)
		m = 2251799813685248;
	i = -1;
	while (++i < new_exp)
	{
		if (m & bin_mantis)
			tab = int_addone(tab, size_dec, 1);
		else
			tab = int_addone(tab, size_dec, 0);
		size_dec++;
		m >>= 1;
	}
	*decimal = calc_tab(tab, size_dec);
	m = 1;
	i = -1;
	while (++i < 52 - new_exp - 1)
		m <<= 1;
	while (m)
	{
		printf("m: %lld\n", m);
		if (m & bin_mantis)
			bat = int_addone(bat, size, 1);
		else
			bat = int_addone(bat, size, 0);
		size++;
		m >>= 1;
	}
	return  (calc_bat(bat, size));
}

void		conv_lf(t_lst *lst, t_chr **mychr, va_list ap)
{
	t_double				db;
	unsigned long int 			entier;
	unsigned long long int			fract;

	db.d = (double)va_arg(ap, double);
	if (lst->format->precis == -1)
		lst->format->precis = 6;
	if (!db.zone.mantissa && !db.zone.exponent)
	{
		if (db.zone.sign)
			(*mychr)->str = ft_strdup("-0");
		else
			(*mychr)->str = ft_strdup("0");
		(*mychr)->len = db.zone.sign + 1;
		return ;
	}
	if (!db.zone.mantissa && (int_exp(db.zone.exponent, D_BIAS) == 2047))
	{
		if  (db.zone.sign)
			(*mychr)->str = ft_strdup("-inf");
		else
			(*mychr)->str = ft_strdup("inf");
		(*mychr)->len = db.zone.sign + 3;
		return ;
	}
	if (int_mants(db.zone.mantissa, D_BIAS) && (int_exp(db.zone.exponent, D_BIAS) == 2047))
	{
		(*mychr)->str = ft_strdup("nan");
		(*mychr)->len = 3;
	}
	fract = get_decimal(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS, &entier);
	printf("%f\n", db.d);
	printf("mantis: %llx\n", (unsigned long long int)db.zone.mantissa);
	printf("expo  : %s\n", ft_itoa_base(db.zone.exponent, 2));
	printf("sign  : %s\n", ft_itoa_base(db.zone.sign, 2));
	ft_printf("decimal: %lu\n", entier);
	ft_printf("fract  : %llu\n", fract);
	ft_putchar('\n');
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
	lst = parse_format(ap, (char*)format);
	if (!lst)
	{
		put_spstr((char*)format);
		if (format[len_format - 1] == '%')
			return (-1);
		return (ft_strlen(format));
	}
	//print_lst(lst);
	if (!(mychr = load_chr((char*)format, lst)))
		return -1;
	//print_chr(mychr);
	//ft_putendl((char*)format);
	fill_chr(lst, mychr, ap);
	//print_lst(lst);
	//show_lst(lst);
	//print_chr(mychr);
	len = put_chr(mychr);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len);
}
