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
	if ((*str)[i] == '0')
		i++;
	if (ft_strchr("xb", (*str)[i]))
		i++;
	while ((*str)[i] == ' ')
		(*str)[i++] = '0';
	if (ft_strchr(fmt->flag, '#'))
	{
		if (fmt->convers != 'o')
			(*str)[++i] = '0';
		if (fmt->convers == 'b')
			(*str)[1] = 'b';
		else if (fmt->convers == 'x' || fmt->convers == 'X')
			(*str)[1] = 'x';
	}
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

void		precis_o_udi(char **str, t_format *fmt, size_t nbr_len)
{
	int	i;
	int	n_z;

	i = -1;
	n_z = (fmt->precis > (int)nbr_len) ? fmt->precis - (int)nbr_len : (int)nbr_len;
	if (n_z <= 0)
		return ;
	while ((*str)[++i] == ' ');
	while (n_z--)
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
			flag_plus(&nbr, lst->format->convers);
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
			precis_o_udi(&str, lst->format, ft_strlen(nbr));
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

static char	*fill_p_str(char *nbr, size_t nbr_size, t_format *fmt)
{
	char		*str;
	size_t		size;
	size_t		i;

	i = 0;
	size = (fmt->width > (fmt->precis + 2)) ? fmt->width : fmt->precis + 2;
	(size < nbr_size) ? size = nbr_size : 0;
	if (!(str = ft_strnew(size)))
		return 0;
	if (!ft_strchr(fmt->flag, '-'))
	{
		while (i < (size - nbr_size + 1))
			str[i++] = ' ';
		ft_strcpy(&str[--i], nbr);
	}
	else
	{
		ft_strcpy(str, nbr);
		i = ft_strlen(str) - 1;
		while (++i < size)
			str[i] = ' ';
	}
	return (str);
}

void		conv_p(t_lst *lst, t_chr **mychr, va_list ap)
{
	char	*str;
	char	*nbr;
	size_t	size_nbr;

	flag_star(lst->format, ap);
	if (flag_dollar(lst))
		nbr = ft_utoa_base((size_t)va_arg(*(lst->arglist), void*), 16);
	else
		nbr = ft_utoa_base((size_t)va_arg(ap, void*), 16);
	flag_dash(&nbr, 16);
	if (ft_strchr(lst->format->flag, '+'))
		flag_plus(&nbr, lst->format->convers);
	nbr = ft_strlowcase(nbr);
	size_nbr = ft_strlen(nbr);
	if (ft_strchr(lst->format->flag, ' ') && lst->format->width <= (int)size_nbr)
		flag_space(&nbr, lst->format->flag);
	str = fill_p_str(nbr, size_nbr, lst->format);
	if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)size_nbr)
		zero_dbiouxx(&str, lst->format);
	if (lst->format->precis > 0)
		precis_zero(&str, lst->format->precis - 12);
	(*mychr)->str = str;
	(*mychr)->len = (int)ft_strlen(str);
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

char				*int_addone(char *tab, int oldsize, int data)
{
	char		*new;
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

char				*foisdix(char *str, unsigned int len)
{
	char		*new;
	unsigned int	i;

	i = 0;
	new = ft_strnew(len  + 1);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '0';
	free(str);
	return (new);
}

char            *calc_tab(char *tab, int size, t_format *format)
{
	char		*entier;
	char		*count;
	unsigned int	len;
	int 		debut;
	int 		i;
	int		base;

	base = (format->convers == 'H') ? 16 : 10;
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
			entier = ft_strsum(entier, count, base);
			ft_putstr("\n entierteb: ");
			ft_putstr(entier);
			ft_putstr("\n");
			len = ft_strlen(entier);
		}
		ft_putchar('\n');
		ft_putendl(count);
		count = ft_strmult("2", count, base);
		ft_putstr("\nentini: ");
		ft_putstr(entier);
		ft_putstr("\ncount    : ");
		ft_putstr(count);
		ft_putchar('\n');
		len++;
	}
	entier[len] = '\0';
	return (entier);
}

char		*calc_bat(char *bat, int size, t_format *format)
{
	char		*fract;
	int		i;
	char		*count;
	unsigned int	len;
	int		base;

	i = -1;
	base = (format->convers == 'H') ? 16 : 10;
	fract = ft_strdup("0");
	len = 1;
	count = ft_strdup("5");
	while (bat[--size] == '0');
	while (++i <= size)
	{
		ft_putchar(bat[i]);
		if (bat[i] == '1')
		{
			fract = ft_strsum(fract, count, base);
			//ft_putstr("\n fractdteb: ");
			//ft_putstr(fract);
			//ft_putstr("\n");
			len = ft_strlen(fract);
		}
		/*ft_putchar('\n');
		  ft_putendl(count);*/
		count = ft_strmult("5", count, base);
		/*ft_putstr("\nfractinti: ");
		  ft_putstr(fract);
		  ft_putstr("\ncount    : ");
		  ft_putstr(count);
		  ft_putchar('\n');*/
		fract = foisdix(fract, len);
		len++;
	}
	/*ft_putstr("\nfract: ");
	  ft_putstr(fract);
	  fract[len] = '\0';
	  ft_putchar('\n');*/
	return (fract);
}

char		*get_entier(long exp, long bin_mantis, int bias, t_format *format)
{
	unsigned long long int		m;
	long				new_exp;
	char				*tab;
	int				size_dec;
	int				i;

	tab = NULL;
	size_dec = 0;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	if (new_exp < 0)
		return (ft_strdup("0"));
	m = (bias == D_BIAS) ? 2251799813685248 : 2305843000000000000;
	if (bias == D_BIAS)
	{
		tab = (exp) ? int_addone(tab, size_dec, 1) : int_addone(tab, size_dec, 0);
		size_dec++;
	}
	i = -1;
	while (++i < new_exp)
	{
		tab = (m & bin_mantis) ? int_addone(tab, size_dec, 1) : int_addone(tab, size_dec, 0);
		size_dec++;
		m >>= 1;
	}
	i = -1;
	ft_putstr("\ntabinini ");
	while (++i < size_dec)
		ft_putchar(tab[i]);
	ft_putchar('\n');
	return (calc_tab(tab, size_dec, format));
}


char		*get_fract(long exp, long bin_mantis, int bias, t_format *format)
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
	len_b = (bias = D_BIAS) ? ABS(52 - new_exp - 1) : ABS(63 - new_exp - 1);
	if (new_exp == -1 * bias)
	{
		bat = int_addone(bat, size, 0);
		len_b++;
		size++;
	}
	while (++i < len_b)
		m <<= 1;
	while (m)
	{
		bat = (m & bin_mantis) ? int_addone(bat, size, 1) : int_addone(bat, size, 0);
		size++;
		m >>= 1;
	}
	return  (calc_bat(bat, size, format));
}

int		is_strzero(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

char		*ft_fprecis(char *fract, int precis, int *carry)
{
	char		*str;
	char		*tmp;
	int		len;
	int		i;

	str = ft_strnew(precis);
	len = ft_strlen(fract);
	i = -1;
	if (precis > len)
	{
		while (++i < len)
			str[i] = fract[i];
		while (i < precis)
			str[i++] = '0';
	}
	else
	{
		while (++i < precis)
			str[i] = fract[i];
		if (fract[i] > '4')
		{
			tmp = ft_strsum(str, "1", 10);
			if (ft_strlen(tmp) > (unsigned int)precis)
			{
				i = -1;
				while (str[++i])
					str[i] = '0';
				*carry = 1;
			}
			else
				ft_strswap(&tmp, &str);
			free(tmp);
		}
	}
	free(fract);
	return (str);
}

char		*ft_fwidth(char *str, unsigned int size_str, t_format *format, unsigned int len_f)
{
	unsigned int	i;
	unsigned int	len;
	char		*res;
	char		c;

	c = (ft_strchr(format->flag, '0')) ? '0' : ' ';
	len = format->width - len_f;
	if (format->precis != 0 || ft_strchr(format->flag, '#'))
		len--;
	if (ft_strpbrk(format->flag, "#+")
			|| (ft_strchr(format->flag, ' ') && !ft_strchr(format->flag, '-')))
		len--;
	res = ft_strnew(len);
	ft_putstr("\nlen: ");
	ft_putnbr(len);
	ft_putchar('\n');
	i = 0;
	while (i < len - size_str)
		res[i++] = c;
	i--;
	while (++i < len)
		res[i] = str[i - (len - size_str)];
	free(str);
	return (res);
}

char		*add_sign(char *str)
{
	char		*res;
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(str) + 1;
	res = ft_strnew(len);
	res[0] = '-';
	i = 0;
	while (++i < len)
		res[i] = str[i - 1];
	free(str);
	return (res);
}

int		proccc(char *fract, char *entier, t_chr **mychr, t_ldouble db)
{
	if (!fract && !entier)
	{
		(*mychr)->str = (db.zone.sign) ? ft_strdup("-0") : ft_strdup("0");
		(*mychr)->len = db.zone.sign + 1;
		return (1);
	}
	if (!fract)
	{
		(*mychr)->str = (db.zone.sign) ? ft_strdup("-nan") : ft_strdup("nan");
		(*mychr)->len = db.zone.sign + 3;
		free(entier);
		return (1);
	}
	return (0);
}

void		conv_lfh(t_lst *lst, t_chr **mychr, t_double db)
{
	char				*fract;
	char				*entier;
	unsigned int			len_e;
	unsigned int			len_f;
	unsigned int			len;
	char				*tmp;
	char				*final;
	int				carry;

	carry = 0;
	if (pre_d_calc(db, mychr))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS, lst->format);
	if (db.d < 1 && db.d > 0)
		db.d++;
	if (db.d > -1 && db.d < 0)
		db.d--;
	if (lst->format->convers == 'H')
		flag_dash(&entier, 16);
	flag_apostrophe(&entier, lst->format);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS), db.zone.mantissa, D_BIAS, lst->format);
	printf("\nfract before: %s\n", fract);
	fract = ft_fprecis(fract, lst->format->precis, &carry);
	ft_putchar('\n');
	if (carry == 1)
		entier = (lst->format->convers == 'H') ? ft_strsum(entier, "1", 16) : ft_strsum(entier, "1", 10);
	if (db.zone.sign)
		entier = add_sign(entier);
	len_e = ft_strlen(entier);
	len_f = ft_strlen(fract);
	len = len_e + len_f + 1;
	if (lst->format->width > (int)len && !ft_strchr(lst->format->flag, '-'))
		entier = ft_fwidth(entier, len_e, lst->format, len_f);
	if (ft_strchr(lst->format->flag, '+'))
		flag_plus(&entier, lst->format->convers);
	else if (ft_strchr(lst->format->flag, ' ') && !ft_strchr(lst->format->flag, '-'))
		flag_space(&entier, lst->format->flag);	
	if (ft_strchr(lst->format->flag, '#') || lst->format->precis != 0)
		tmp = ft_strjoin(entier, ".");
	else
		tmp = ft_strjoin(entier, "");
	final = (lst->format->precis > 0) ? ft_strjoin(tmp, fract) : ft_strjoin(tmp, "");
	printf("fract  : %s\n", fract);
	free(tmp);
	free(fract);
	printf("entier: %s\n", entier);
	free(entier);
	(*mychr)->str = final;
	(*mychr)->len = len;
	printf("%.70f\n", db.d);
	printf("mantis: %llx\n", (unsigned long long int)db.zone.mantissa);
	printf("expo  : %s\n", ft_itoa_base(db.zone.exponent, 2));
	printf("sign  : %s\n", ft_itoa_base(db.zone.sign, 2));
	ft_putchar('\n');
}

void            conv_llf(t_lst *lst, t_chr **mychr, va_list ap)
{
	t_ldouble                       db;
	char                            *fract;
	char                            *entier;
	unsigned int                    len_e;
	unsigned int                    len_f;
	unsigned int                    len;
	char                            *tmp;
	char                            *final;
	int                             carry;

	carry = 0;
	flag_star(lst->format, ap);
	db.ld = (flag_dollar(lst)) ? va_arg(*(lst->arglist), long double) : va_arg(ap, long double);
	(lst->format->precis == -1) ? lst->format->precis = 6 : 0;
	if (pre_ld_calc(db, mychr) == 1)
		return ;
	entier = get_entier(int_exp(db.zone.exponent, LD_BIAS), db.zone.mantissa, LD_BIAS, lst->format);
	if (db.ld < 1 && db.ld > 0)
		db.ld++;
	if (db.ld > -1 && db.ld < 0)
		db.ld--;
	flag_apostrophe(&entier, lst->format);
	fract = get_fract(int_exp(db.zone.exponent, LD_BIAS), db.zone.mantissa, LD_BIAS, lst->format);
	//if (!fract || !entier)
	//	if (proccc(entier, fract, mychr, db))
	//		return ;
	//{
	//	(*mychr)->str = ft_strdup("nan");
	//	(*mychr)->len = 3;
	//	return ;
	//}
	printf("\nfract before: %s\n", fract);
	fract = ft_fprecis(fract, lst->format->precis, &carry);
	ft_putchar('\n');
	if (carry == 1)
		entier = ft_strsum(entier, "1", 10);
	if (db.zone.sign)
		entier = add_sign(entier);
	len_e = ft_strlen(entier);
	len_f = ft_strlen(fract);
	len = len_e + len_f + 1;
	if (lst->format->width > (int)len && !ft_strchr(lst->format->flag, '-'))
	{
		entier = ft_fwidth(entier, len_e, lst->format, len_f);
		len = lst->format->width;
	}
	if (ft_strchr(lst->format->flag, '+'))
		flag_plus(&entier, lst->format->convers);
	else if (ft_strchr(lst->format->flag, ' ') && !ft_strchr(lst->format->flag, '-'))
		flag_space(&entier, lst->format->flag);
	len_e = ft_strlen(entier);
	if (ft_strchr(lst->format->flag, '#') || lst->format->precis != 0)
		tmp = ft_strjoin(entier, ".");
	else
		tmp = ft_strjoin(entier, "");
	final = (lst->format->precis > 0) ? ft_strjoin(tmp, fract) : ft_strjoin(tmp, "");
	printf("fract  : %s\n", fract);
	free(tmp);
	free(fract);
	printf("entier: %s\n", entier);
	free(entier);
	(*mychr)->str = final;
	(*mychr)->len = len;
	printf("%.70Lf\n", db.ld);
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
	print_lst(lst);
	if (!(mychr = load_chr((char*)format, lst)))
		return -1;
	print_chr(mychr);
	ft_putendl((char*)format);
	fill_chr(lst, mychr, ap);
	show_lst(lst);
	print_chr(mychr);
	len = put_chr(mychr);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len);
}

unsigned int	get_chr_len(t_chr *mychr)
{
	unsigned int	len;

	len = 0;
	while (mychr)
	{
		len += mychr->len;
		mychr = mychr->next;
	}
	return (len);
}

char	*str_chr(t_chr *mychr, unsigned int len_str)
{
	char		*str;
	unsigned int	i;
	unsigned int	j;

	str = (char*)malloc(sizeof(char) * len_str + 1);
	str[len_str] = '\0';
	i = 0;
	while (mychr && i < len_str)
	{
		j = 0;
		while (j < mychr->len && i < len_str)
		{
			str[i] = (mychr->str)[j];
			j++;
			i++;
		}
		mychr = mychr->next;
	}
	return (str);
}

int             ft_sprintf(char **str, const char *format, ...)
{
	t_chr           *mychr;
	t_lst           *lst;
	va_list         ap;
	unsigned int	len;
	unsigned int	len_format;

	len_format = 0;
	while (format[len_format++]);
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
	print_lst(lst);
	//show_lst(lst);
	//print_chr(mychr);
	len = get_chr_len(mychr);
	*str = str_chr(mychr, len);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len);
}

int             ft_snprintf(char **str, size_t n, const char *format, ...)
{
	t_chr           *mychr;
	t_lst           *lst;
	va_list         ap;
	unsigned int    len;
	unsigned int    len_format;

	len_format = 0;
	while (format[len_format++]);
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
	print_lst(lst);
	//show_lst(lst);
	//print_chr(mychr);
	len = get_chr_len(mychr);
	if (len > n)
		len = n;
	*str = str_chr(mychr, n);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len);
}

int             ft_dprintf(int fd, const char *format, ...)
{
	t_chr           *mychr;
	t_lst           *lst;
	va_list         ap;
	int             len;
	int             len_format;

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
	print_lst(lst);
	//show_lst(lst);
	//print_chr(mychr);
	len = put_chr_fd(fd, mychr);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len);
}

int             ft_dnprintf(int fd, size_t n, const char *format, ...)
{
	t_chr           *mychr;
	t_lst           *lst;
	va_list         ap;
	int             len;
	int             len_format;

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
	print_lst(lst);
	//show_lst(lst);
	//print_chr(mychr);
	len = put_chr_nfd(fd, n, mychr);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len);
}

int             ft_vprintf(const char *format, va_list ap)
{
	t_chr           *mychr;
	t_lst           *lst;
	int             len;
	int             len_format;

	len = 0;
	len_format = 0;
	while (format[len_format])
		len_format++;
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
	print_lst(lst);
	//show_lst(lst);
	//print_chr(mychr);
	len = put_chr(mychr);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len);
}
