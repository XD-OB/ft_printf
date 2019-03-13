#include "ft_printf.h"

void     print_chr(t_chr *chr)
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

void     show_lst(t_lst *lst)
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
