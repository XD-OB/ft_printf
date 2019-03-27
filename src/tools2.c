#include "ft_printf.h"

int             is_format(char c)
{
        int             i;
        char    *ref;

        i = 0;
        ref = "cspdiouxXfegrkb}%";
        while (ref[i])
                if (c == ref[i++])
                        return (1);
        return (0);
}

int             is_postflag(char c)
{
        int             i;
        char    *ref;

        i = 0;
        ref = "lLh$0+-r";
        while (ref[i])
                if (c == ref[i++])
                        return (1);
        return (0);
}

int             is_preflag(char c)
{
        int     i;
        char    *ref;

        i = 0;
        ref = " 0+-#'*r";
        while (ref[i])
                if (c == ref[i++])
                        return (1);
        return (0);
}

void    put_spstr(char *str)
{
        while (*str)
        {
                if (*str != '%')
                        ft_putchar(*str);
                str++;
        }
}
