#include "ft_printf.h"

static int      base_detect(char c)
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

static size_t   cast_xxoub(va_list ap, char *flag)
{
        size_t  n;

        if (ft_strstr(flag, "hh"))
                n = (unsigned char)va_arg(ap, unsigned int);
        else if (ft_strstr(flag, "h"))
                n = (unsigned short int)va_arg(ap, unsigned int);
        else if (ft_strstr(flag, "ll"))
                n = (unsigned long long int)va_arg(ap, unsigned long long int);
        else if (ft_strstr(flag, "l"))
                n = (unsigned long int)va_arg(ap, unsigned long int);
        else
                n = (unsigned int)va_arg(ap, unsigned int);
        return (n);
}

static char     *fill_xxoub_str(t_format *fmt, char *nbr, size_t size_nbr)
{
        size_t  size;
        char    *str;
        size_t  i;

        size = (fmt->width > fmt->precis) ? fmt->width : fmt->precis;
        (size < size_nbr) ? size = size_nbr : 0;
        if (!(str = ft_strnew(size)))
                return 0;
        if (ft_strchr(fmt->flag, '-'))
        {
                ft_strcpy(str, nbr);
                i = size_nbr;
                while (i < size)
                        str[i++] = ' ';
        }
        else
        {
                i = 0;
                while (i < (size - size_nbr + 1))
                        str[i++] = ' ';
                ft_strcpy(&str[--i], nbr);
                if (ft_strchr(fmt->flag, '0') && fmt->width > (int)(size_nbr))
                        zero_dbiouxx(&str, fmt);
        }
        return (str);
}

void            conv_xxoub(t_lst *lst, t_chr **mychr, va_list ap)
{
        char    *str;
        char    *nbr;
        size_t  n;
        int     i;

        flag_star(lst->format, ap);
        n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format->flag)
                : cast_xxoub(ap, lst->format->flag);
        if (n == 0 && !lst->format->precis)
                (*mychr)->str = ft_strnew(0);
        else
        {
                i = base_detect(lst->format->convers);
                nbr = ft_utoa_base(n, i);
                if (n && ft_strchr(lst->format->flag, '#') && lst->format->convers != 'u')
                        flag_dash(&nbr, i);
                flag_apostrophe(&nbr, lst->format);
                str = fill_xxoub_str(lst->format, nbr, ft_strlen(nbr));
                (lst->format->precis > 0) ? precis_o_udi(&str, lst->format, ft_strlen(nbr)) : 0;
                (lst->format->convers == 'x') ? str = ft_strlowcase(str) : 0;
                (lst->format->convers == 'X') ? str = ft_strupcase(str) : 0;
		if (lst->format->precis > 0 && lst->format->convers == 'u')
			precis_o_udi(&str, lst->format, ft_strlen(nbr));
                (*mychr)->str = str;
                free(nbr);
        }
        (*mychr)->len = ft_strlen(str);
}
