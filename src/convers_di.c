#include "ft_printf.h"

static long long int    cast_di(va_list ap, char *flag)
{
        long long int   d;

        if (ft_strstr(flag, "hh"))
                d = (char)va_arg(ap, int);
        else if (ft_strstr(flag, "h"))
                d = (short int)va_arg(ap, int);
        else if (ft_strstr(flag, "ll"))
                d = (long long int)va_arg(ap, long long int);
        else if (ft_strstr(flag, "l"))
                d = (long int)va_arg(ap, long int);
        else
                d = (int)va_arg(ap, int);
        return (d);
}

static void             fill_di_str(t_chr **mychr, t_format *fmt, char *nbr, long long int d)
{
        size_t          size;
        size_t          nbr_size;
        char            *str;
        int             i;

        nbr_size = ft_strlen(nbr);
        size = ft_max(fmt->width, fmt->precis);
        size = ft_max(size, nbr_size);
        if (!(str = ft_strnew(size)))
                return ;
        i = -1;
        while (++i < (int)(size - nbr_size))
                str[i] = (ft_strchr(fmt->flag, '0')) ? '0' : ' ';
        if (d < 0 && ft_strchr(fmt->flag, '0'))
        {
                nbr[0] = '0';
                str[0] = '-';
        }
        ft_strcat(str, nbr);
        if (ft_strchr(fmt->flag, '0') && fmt->width > (int)(nbr_size) && !fmt->precis)
                zero_dbiouxx(&str, fmt);
        if (fmt->precis > 0)
                precis_o_udi(&str, fmt, nbr_size);
        (*mychr)->str = str;
        (*mychr)->len = size;
}

void                    conv_di(t_lst *lst, t_chr **mychr, va_list ap)
{
        char            *nbr;
        long long int   d;

        flag_star(lst->format, ap);
        if (flag_dollar(lst))
                d = cast_di(*(lst->arglist), lst->format->flag);
        else
                d = cast_di(ap, lst->format->flag);
        if (d == 0 && !lst->format->precis)
        {
                (*mychr)->str = ft_strnew(0);
                (*mychr)->len = 0;
        }
        else
        {
                nbr = ft_itoa(d);
                flag_apostrophe(&nbr, lst->format);
                if (ft_strchr(lst->format->flag, '+'))
                        flag_plus(&nbr, lst->format->convers);
                if (d >= 0 && ft_strchr(lst->format->flag, ' '))
                        flag_space(&nbr, lst->format->flag);
                fill_di_str(mychr, lst->format, nbr, d);
                free(nbr);
        }
}
