#include "ft_printf.h"

static char     *dash_xob(char *nbr, int size, int base)
{
        char    *str;
        int     i;

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

void            flag_dash(char **nbr, int base)
{
        int     size;
        char    *tmp;

        if (base != 16 && base != 8 && base != 2)
                return ;
        tmp = *nbr;
        size = ft_strlen(*nbr);
        *nbr = dash_xob(*nbr, size, base);
        free (tmp);
}

void            flag_apostrophe(char **str, t_format *fmt)
{
        int     prev_len;
        int     count;
        char    *res;
        int     i;
        int     j;

        if (ft_strchr(fmt->flag, '\'') && ft_strchr("udi", fmt->convers))
        {
                ft_putstr("hi\n");
                prev_len = ft_strlen(*str);
                i = prev_len;
                j = prev_len + (prev_len - 1) / 3;
                res = (char*)malloc(sizeof(char) * (j + 1));
                res[j] = '\0';
                count = 1;
                while (--i >= 0 && --j >= 0)
                {
                        res[j] = (*str)[i];
                        if (count % 3 == 0 && j > 0)
                                res[--j] = ',';
                        count++;
                }
                free(*str);
                *str = res;
        }
}