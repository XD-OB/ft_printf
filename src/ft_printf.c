/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 14:46:18 by obelouch          #+#    #+#             */
/*   Updated: 2019/03/07 23:19:34 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flag_plus(char **nbr)
{
	char	*str;
	int	len;

	len = ft_strlen(*nbr) + 1;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (ft_atoi(*nbr) < 0)
		str[0] = '-';
	else
		str[0] = '+';
	str[len] = '\0';
	ft_strcpy(&str[1], *nbr);
	free (*nbr);
	*nbr = str;
}

void            flag_space(char **nbr, char *flag)
{
	char    *str;
	int     len;

	if (!ft_strchr(flag, '+'))
	{
		len = ft_strlen(*nbr) + 1;
		str = (char*)malloc(sizeof(char) * (len + 1));
		if (ft_atoi(*nbr) >= 0)
			str[0] = ' ';
		str[len] = '\0';
		ft_strcpy(&str[1], *nbr);
		free (*nbr);
		*nbr = str;
	}
}

void		flag_zero(char **str, t_format *format)
{
	int	i;

	if ((format->precis == 0 || format->convers == 'f')
			&& !ft_strchr(format->flag, '+'))
	{
		i = -1;
		while (++i < (format->width - (int)ft_strlen(*str)))
			(*str)[i] = '0';
	}
}

char		*no_print_1(char c)
{
	if (c == 0)
		return (ft_strdup("[NUL]"));
	if (c == 1)
		return (ft_strdup("[SOH]"));
	if (c == 2)
		return (ft_strdup("[STX]"));
	if (c == 3)
		return (ft_strdup("[ETX]"));
	if (c == 4)
		return (ft_strdup("[EOT]"));
	if (c == 5)
		return (ft_strdup("[ENQ]"));
	if (c == 6)
		return (ft_strdup("[ACK]"));
	if (c == 7)
		return (ft_strdup("[BEL]"));
	if (c == 8)
		return (ft_strdup("[BS ]"));
	if (c == 9)
		return (ft_strdup("[HT ]"));
	if (c == 10)
		return (ft_strdup("[LF ]"));
	return (ft_strdup("[VT ]"));
}


char		*no_print_2(char c)
{
	if (c == 12)
		return (ft_strdup("[FF ]"));
	if (c == 13)
		return (ft_strdup("[CR ]"));
	if (c == 14)
		return (ft_strdup("[SO ]"));
	if (c == 15)
		return (ft_strdup("[SI ]"));
	if (c == 16)
		return (ft_strdup("[DLE]"));
	if (c == 17)
		return (ft_strdup("[DC1]"));
	if (c == 18)
		return (ft_strdup("[DC2]"));
	if (c == 19)
		return (ft_strdup("[DC3]"));
	if (c == 20)
		return (ft_strdup("[DC4]"));
	if (c == 21)
		return (ft_strdup("[NAK]"));
	return (ft_strdup("[SYN]"));
}

char		*no_print_3(char c)
{
	if (c == 23)
		return (ft_strdup("[ETB]"));
	if (c == 24)
		return (ft_strdup("[CAN]"));
	if (c == 25)
		return (ft_strdup("[EM ]"));
	if (c == 26)
		return (ft_strdup("[SUB]"));
	if (c == 27)
		return (ft_strdup("[ESC]"));
	if (c == 28)
		return (ft_strdup("[FS ]"));
	if (c == 29)
		return (ft_strdup("[GS ]"));
	if (c == 30)
		return (ft_strdup("[RS ]"));
	if (c == 31)
		return (ft_strdup("[US ]"));
	return (ft_strdup("[DEL]"));
}

char		*flag_r(char c)
{
	if (c < 12)
		return (no_print_1(c));
	if (c >= 12 && c < 23)
		return (no_print_2(c));
	if (c == 127 || (c >= 23 && c < 32))
		return (no_print_3(c));
	return (NULL);
}

static char	*dash_xob(char *nbr, int size, int base)
{
	char	*str;
	int	i;

	i = (base == 8) ? 1 : 2;
	size += i;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[0] = '0';
	(base == 16) ? str[1] = 'X' : 0;
	(base == 2) ? str[1] = 'b' : 0;
	ft_strcpy(&str[i], nbr);
	str[size] = '\0';
	return (str);
}

void		flag_dash(char **nbr, int base)
{
	int	size;
	char	*tmp;

	if (base != 16 && base != 8 && base != 2)
		return ;
	tmp = *nbr;
	size = ft_strlen(*nbr);
	*nbr = dash_xob(*nbr, size, base);
	free (tmp);
}

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
	size_t	size;
	char	*str;
	char	*nbr;
	int		i;
	long long int	d;

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

void		conv_s(t_lst *lst, t_chr **mychr, const char *s)
{
	int	count_np;
	int	i;
	int	len;
	char	*str;

	if (s == NULL)
	{
		(*mychr)->str = ft_strdup("(null)");
		(*mychr)->len = 6;
		return ;
	}
	len = ft_strlen(s);
	if (lst->format->width > len)
		len = lst->format->width;
	i = 0;
	count_np = 0;
	while (s[i])
	{
		if ((s[i] >= 0 && s[i] < 32) || s[i] == 127)
			count_np++;
		i++;
	}
	if (!(str = (char*)malloc(sizeof(char) * (len + (count_np * 5) + 1))))
		return ;
	str[len] = '\0';
	i = -1;
	if ((ft_strchr(lst->format->flag, '0') && !ft_strchr(lst->format->flag, '-'))
			|| !ft_strpbrk(lst->format->flag, "0-+"))
	{
		if (len == lst->format->width)
			while (++i < len - (int)strlen(s))
				str[i] = ' ';
		//i--;
		while (++i < len)
		{
			if (ft_isprint(s[i - len + (int)ft_strlen(s)]) || !ft_strchr(lst->format->flag, 'r'))
				str[i] = s[i - len + (int)ft_strlen(s)];
			else
			{
				ft_strcat(&str[i], flag_r(s[i - len + (int)ft_strlen(s)]));
				i += 5;
			}
		}
	}
	else 
	{
		while (++i < (int)ft_strlen(s))
		{
			if (ft_isprint(s[i]) || !ft_strchr(lst->format->flag, 'r'))
				str[i] = s[i];
			else
			{
				ft_strcat(&str[i], flag_r(s[i]));
				i += 5;
			}
		}
		if (len == lst->format->width)
			while (i < len)
				str[i++] = ' ';
	}
	(*mychr)->str = str;
	(*mychr)->len = len;
}

void		conv_c(t_lst *lst, t_chr **mychr, char c)
{
	int	i;
	int	len;
	char	*str;

	i = -1;
	len = lst->format->width;
	if (lst->format->width < 2 || ft_strpbrk(lst->format->flag, "+-0#"))
		len = 1;
	str = (char*)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (++i < len - 1)
		str[i] = ' ';
	str[i] = c;
	(*mychr)->str = str;
	(*mychr)->len = len;
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

void		conv_p(t_lst *lst, t_chr **mychr, size_t addr)
{
	char	*str;
	char	*nbr;
	size_t	size;
	int	i;

	nbr = ft_utoa_base(addr, 16);
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

void		conv_invalid(t_chr **mychr, t_format *format)
{
	int		i;

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

void		conv_color(t_lst *lst, t_chr **mychr)
{
	if (lst->format->convers != '}')
	{
		conv_invalid(mychr, lst->format);
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
		conv_invalid(mychr, lst->format);
}

void		fill_chr(t_lst *lst, t_chr *chr, va_list ap)
{
	while (lst)
	{
		while (chr && chr->str)
			chr = chr->next;
		if (ft_strchr("xXoub", lst->format->convers))
			conv_xxoub(lst, &chr, ap);
		else if (lst->format->convers == '}')
			conv_color(lst, &chr);
		else if (lst->format->convers == 'p')
			conv_p(lst, &chr, (size_t)va_arg(ap, void*));
		else if (ft_strchr("di", lst->format->convers))
			conv_di(lst, &chr, ap);
		else if (lst->format->convers == 's')
			conv_s(lst, &chr, va_arg(ap, const char*));
		else if (lst->format->convers == 'c')
			conv_c(lst, &chr, (char)va_arg(ap, int));
		else if (lst->format->convers == '%')
			conv_percent(&chr);
		else
			conv_invalid(&chr, lst->format);
		lst = lst->next;
		chr = chr->next;
	}
}

char		*cut_str(char *str, int p1, int p2)
{
	int	i;
	char	*ret;

	i = p1 - 1;
	if (!(ret = (char*)malloc(sizeof(char) * (p2 - p1 + 2))))
		return NULL;
	while (++i <= p2)
		ret[i - p1] = str[i];
	ret[i - p1] = '\0';
	return (ret);

}

void		init_chr(t_chr **chr)
{
	(*chr)->str = NULL;
	(*chr)->len = 0;
	(*chr)->next = NULL;
}

t_chr		*load_chr(char *format, t_lst *lst)
{
	t_chr	*mychr;
	t_chr	*curr;
	int	p1;
	int	p2;

	if (!(mychr = (t_chr*)malloc(sizeof(t_chr))))
		return NULL;
	init_chr(&mychr);
	p1 = 0;
	curr = mychr;
	while (lst)
	{
		p2 = lst->format->pos - 1;
		if (p2 >= p1)
		{
			curr->str = cut_str(format, p1, p2);
			curr->len = p2 - p1 + 1;
			curr->next = (t_chr*)malloc(sizeof(t_chr));
			curr = curr->next;
			init_chr(&curr);
		}
		p1 = (p2 >= 0) ? p2 : 0;
		while (format[p1] != lst->format->convers)
			p1++;
		if (format[++p1] == '%')
			p1++;
		if (lst->next)
		{
			curr->next = (t_chr*)malloc(sizeof(t_chr));
			curr = curr->next;
			init_chr(&curr);
		}
		lst = lst->next;
	}
	if (format[p1])
	{
		curr->next = (t_chr*)malloc(sizeof(t_chr));
		curr = curr->next;
		curr->str = ft_strdup(&format[p1]);
		curr->len = ft_strlen(&format[p1]);
		curr->next = NULL;
	}
	return (mychr);
}

int		put_chr(t_chr *chr)
{
	int	len;

	len = 0;
	while (chr)
	{
		ft_putstr(chr->str);
		len += chr->len;
		chr = chr->next;
	}
	return (len);
}

static void	print_chr(t_chr *chr)
{
	while (chr)
	{
		if (chr->str)
			write(1, chr->str, chr->len);
		else
			write(1, "strO", 4);
		write(1, " -> ", 4);
		chr = chr->next;
	}
	write(1, "NULL", 4);
	ft_putchar('\n');
}

static void	show_lst(t_lst *lst)
{
	while (lst)
	{
		write(1, &(lst->format->convers), 1);
		write(1, " -> ", 4);
		lst = lst->next;
	}
	write(1, "NULL", 4);
	ft_putchar('\n');
}

void		free_chr(t_chr *chr)
{
	t_chr	*tmp;

	while (chr)
	{
		tmp = chr;
		chr = chr->next;
		free (tmp);
	}
}

int		ft_printf(const char *format, ...)
{
	t_chr		*mychr;
	t_lst		*lst;
	va_list		ap;
	int		len;

	len = 0;
	va_start(ap, format);
	lst = parse_format((char*)format);
	if (!lst)
	{
		put_spstr((char*)format);
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
	return (len);
}
