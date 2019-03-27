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

void    print_lst(t_lst *lst)
{
        t_lst   *curr;

        curr = lst;
        while (curr)
        {
                ft_putstr("num argm: ");
                ft_putnbr(curr->format->argn);
                ft_putchar('\n');
                ft_putstr("position: ");
                ft_putnbr(curr->format->pos);
                ft_putchar('\n');
                ft_putstr("flags   : ");
                ft_putstr(curr->format->flag);
                ft_putchar('\n');
                ft_putstr("precision: ");
                ft_putnbr(curr->format->precis);
                ft_putchar('\n');
                ft_putstr("width    : ");
                ft_putnbr(curr->format->width);
                ft_putchar('\n');
                ft_putstr("conversion: ");
                ft_putchar(curr->format->convers);
                ft_putchar('\n');
                ft_putstr("\nNEXT_NODE\n\n");
                curr = curr->next;
        }
        ft_putstr("Size of list:\t");
        ft_putnbr(lstlen(lst));
        ft_putchar('\n');
}
