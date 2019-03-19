#include "ft_printf.h"

t_chr           *load_chr(char *format, t_lst *lst)
{
        t_chr   *mychr;
        t_chr   *curr;
        int     p1;
        int     p2;

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

void            fill_chr(t_lst *lst, t_chr *chr, va_list ap)
{
        while (lst)
        {
                while (chr && chr->str)
                        chr = chr->next;
		if (ft_strchr("fH", lst->format->convers))
			conv_lf(lst, &chr, ap);
		else if (lst->format->convers == 'k')
                        conv_k(lst->format, &chr, ap);
                else if (ft_strchr("xXoub", lst->format->convers))
                        conv_xxoub(lst, &chr, ap);
                else if (lst->format->convers == '}')
                        conv_color(lst, &chr, ap);
                else if (lst->format->convers == 'p')
                        conv_p(lst, &chr, ap);
                else if (ft_strchr("di", lst->format->convers))
                        conv_di(lst, &chr, ap);
                else if (lst->format->convers == 's')
                        conv_s(lst, &chr, ap);
                else if (lst->format->convers == 'c')
                        conv_c(lst, &chr, ap);
                else if (lst->format->convers == '%')
                        conv_percent(&chr);
                else
                        conv_invalid(&chr, lst->format, ap);
                lst = lst->next;
                chr = chr->next;
        }
}

int             put_chr(t_chr *chr)
{
        int     len;

        len = 0;
        while (chr)
        {
                ft_putstr(chr->str);
                len += chr->len;
                chr = chr->next;
        }
        return (len);
}
