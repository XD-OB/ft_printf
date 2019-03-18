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

# define ABS(x) (x < 0) ? -x : x;

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

char				*foisdix(char *str, unsigned int len)
{
	char		*new;
	unsigned int	i;

	i = 0;
	new = (char*)malloc(sizeof(char) * (len  + 2));
	new[len + 1] = '\0';
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '0';
	free(str);
	return (new);
}

static int	*ft_strmulti1(char *num1, char *num2, int *k)
{
	int		len[2];
	int		*prod;
	int		i;
	int		j;

	len[0] = ft_strlen(num1);
	len[1] = ft_strlen(num2);
	prod = (int *)ft_strnew((len[0] + len[1] + 1) * sizeof(int));
	*k = 0;
	i = len[0];
	while (--i >= 0)
	{
		(*k) = len[0] - 1 - i;
		j = len[1];
		while (--j >= 0)
			prod[(*k)++] += (num1[i] - '0') * (num2[j] - '0');
	}
	(*k)++;
	return (prod);
}

char		*ft_strmulti(char *num1, char *num2)
{
	int		c;
	int		i;
	int		k;
	int		*prod;

	if (num1 == NULL || num2 == NULL)
		return (NULL);
	i = -1;
	prod = ft_strmulti1(num1, num2, &k);
	while (++i < k - 1)
	{
		c = prod[i] / 10;
		prod[i] = prod[i] % 10;
		prod[i + 1] += c;
	}
	while (k > 1 && prod[k - 1] == 0)
		k--;
	num1 = ft_strnew((k + 1));
	i = -1;
	while (++i < k)
		num1[i] = prod[k - 1 - i] + '0';
	num1[k] = '\0';
	free(prod);
	return (num1);
}

char            *calc_tab(char *tab, int size)
{
        char		*entier;
	char		*count;
	unsigned int	len;
        int 		i;
        int 		debut;

        entier = ft_strdup("0");
	count = ft_strdup("1");
	len =  1;
	debut = -1;
	while(tab[++debut] == '0');
        i = size;
        while (--i >= debut)
        {
		if (tab[i] == '1')
		{
			entier = ft_strsum(entier, count);
			ft_putstr("\n entierteb: ");
			ft_putstr(entier);
			ft_putstr("\n");
			len = ft_strlen(entier);
		}
		ft_putchar('\n');
                ft_putendl(count);
                count = ft_strmulti("2", count);
                ft_putstr("\nentini: ");
                ft_putstr(entier);
                ft_putstr("\ncount    : ");
                ft_putstr(count);
                ft_putchar('\n');
                len++;
        }
	entier[len] = '\0';
	i = -1;
        return (entier);
}

char		*calc_bat(char *bat, int size)
{
	char		*fract;
	int		i;
	char		*count;
	unsigned int	len;

	i = -1;
	fract = ft_strdup("0");
	len = 1;
	count = ft_strdup("5");
	while (bat[--size] == '0');
	while (++i <= size)
	{
		ft_putchar(bat[i]);
		if (bat[i] == '1')
		{
			fract = ft_strsum(fract, count);
			ft_putstr("\n fractdteb: ");
			ft_putstr(fract);
			ft_putstr("\n");
			len = ft_strlen(fract);
		}
		ft_putchar('\n');
		ft_putendl(count);
		count = ft_strmulti("5", count);
		ft_putstr("\nfractinti: ");
		ft_putstr(fract);
		ft_putstr("\ncount    : ");
		ft_putstr(count);
		ft_putchar('\n');
		fract = foisdix(fract, len);
		len++;
	}
	ft_putstr("\nfract: ");
	ft_putstr(fract);
	fract[len] = '\0';
	ft_putchar('\n');
	return (fract);
}

char		*get_decimal(long exp, long bin_mantis, int bias)
{
	int				i;
	unsigned long long int		m;
	long				new_exp;
	char				*tab;
	int				size_dec;

	tab = NULL;
	size_dec = 0;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	if (new_exp < 0)
		return (0);
	if (bias == D_BIAS)
		m = 2251799813685248;
	if (bias == LD_BIAS)
		m = 2305843000000000000;
	if (exp)
		tab = int_addone(tab, size_dec, 1);
	else
		tab = int_addone(tab, size_dec, 0);
	size_dec++;
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
	i = -1;
	ft_putstr("\ntabinini ");
	while (++i < size_dec)
		ft_putchar(tab[i]);
	ft_putchar('\n');
	return (calc_tab(tab, size_dec));
}


char		*get_fract(long exp, long bin_mantis, int bias)
{
	unsigned long long	m;
	int			len_b;
	unsigned int		size;
	int			i;
	char			*bat;
	long			new_exp;

	bat = NULL;
	size = 0;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	m = 1;
	i = -1;
	len_b = ABS(52 - new_exp - 1);
	ft_putchar('\n');
	ft_putnbr(len_b);
	ft_putchar('\n');
	if (bias == LD_BIAS)
		len_b = ABS(63 - new_exp - 1);
	if (new_exp == -1023)
	{
		bat = int_addone(bat, size, 0);
		len_b++;
		size++;
	}
	while (++i < len_b)
		m <<= 1;
	while (m)
	{
		//printf("m: %lld\n", m);
		if (m & bin_mantis)
			bat = int_addone(bat, size, 1);
		else
			bat = int_addone(bat, size, 0);
		size++;
		m >>= 1;
	}
	return  (calc_bat(bat, size));
}

char		*ft_fprecis(char *fract, int precis)
{
	char		*str;
	int		len;
	int		i;

	str = (char*)malloc(sizeof(char) * (precis + 1));
	str[precis] = '\0';
	len = ft_strlen(fract);
	if (len == precis)
		return (fract);
	if (precis > len)
	{
		i = -1;
		while (++i < len)
			str[i] = fract[i];
		while (i < precis)
			str[i++] = '0';
	}
	else
	{
		i = -1;
		while (++i < precis)
			str[i] = fract[i];
		if (fract[i] > 4 && fract[0] != '9')
			str = ft_strsum(str, "1");
	}
	free(fract);
	return (str);
}

char		*ft_fwidth(char *str, unsigned int size_str, unsigned int len)
{
	char	*res;

	res = (char*)malloc(sizeof(char) * len);
	res[len] = '\0';
	while (size_str--)
		res[--len] = str[size_str];
	while (len--)
		res[len] = ' ';
	free(str);
	return (res);
}

void		conv_lf(t_lst *lst, t_chr **mychr, va_list ap)
{
	t_double			db;
	char				*fract;
	char				*entier;
	unsigned int			len_e;
	unsigned int			len_f;
	unsigned int			len;
	char				*tmp;
	char				*final;

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
	if (!db.zone.mantissa && (int_exp(db.zone.exponent, D_BIAS) == MAX_D))
	{
		if  (db.zone.sign)
			(*mychr)->str = ft_strdup("-inf");
		else
			(*mychr)->str = ft_strdup("inf");
		(*mychr)->len = db.zone.sign + 3;
		return ;
	}
	if (int_mants(db.zone.mantissa, D_BIAS) && (int_exp(db.zone.exponent, D_BIAS) == MAX_D))
	{
		(*mychr)->str = ft_strdup("nan");
		(*mychr)->len = 3;
	}
	if (db.d < 1 && db.d > 0)
		db.d++;
	if (db.d > -1 && db.d < 0)
		db.d--;
	entier = get_decimal(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS);
	len_e = ft_strlen(entier);
	fract = ft_fprecis(fract, lst->format->precis);
	len_f = ft_strlen(fract);
	len = len_e + len_f + 1;
	if (lst->format->width > (int)len)
	{
		ft_fwidth(entier, len - len_f, lst->format->width - len_f);
		len = lst->format->width;
	}
	tmp = ft_strjoin(entier, ".");
	final = ft_strjoin(tmp, fract);
	ft_printf("entier: %s\n", entier);
	ft_printf("fract  : %s\n", fract);
	free(tmp);
	free(entier);
	free(fract);
	(*mychr)->str = final;
	(*mychr)->len = len;
	printf("%.70f\n", db.d);
	printf("mantis: %llx\n", (unsigned long long int)db.zone.mantissa);
	printf("expo  : %s\n", ft_itoa_base(db.zone.exponent, 2));
	printf("sign  : %s\n", ft_itoa_base(db.zone.sign, 2));
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
