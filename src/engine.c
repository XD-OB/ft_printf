#include "ft_printf.h"

t_chr           *load_chr(char *format, t_lst *lst)
{
        t_chr   *mychr;
        t_chr   *curr;
        int     p[2];

        if (!(mychr = (t_chr*)malloc(sizeof(t_chr))))
                return NULL;
        init_chr(&mychr);
        p[0] = 0;
        curr = mychr;
        while (lst)
        {
                p[1] = lst->format->pos - 1;
                if (p[1] >= p[0])
                {
                        curr->str = cut_str(format, p[0], p[1]);
                        curr->len = p[1] - p[0] + 1;
                        curr->next = (t_chr*)malloc(sizeof(t_chr));
                        curr = curr->next;
                        init_chr(&curr);
                }
                p[0] = (p[1] >= 0) ? p[1] : 0;
                if (format[p[0]] == '%')
                        p[0]++;
                while (format[p[0]] != lst->format->convers)
                        p[0]++;
                if (lst->next)
                {
                        curr->next = (t_chr*)malloc(sizeof(t_chr));
                        curr = curr->next;
                        init_chr(&curr);
                }
                lst = lst->next;
		p[0]++;
        }
        if (format[p[0]] && format[p[0]] != '%')
        {
                curr->next = (t_chr*)malloc(sizeof(t_chr));
                curr = curr->next;
                curr->str = ft_strdup(&format[p[0]]);
                curr->len = ft_strlen(&format[p[0]]);
                curr->next = NULL;
        }
        return (mychr);
}

static void	some_convers(t_lst *lst, t_chr *chr, va_list ap)
{
	if (lst->format->convers == 's')
		conv_s(lst, &chr, ap);
	else if (lst->format->convers == 'c')
		conv_c(lst, &chr, ap);
	else if (lst->format->convers == 'k')
       		conv_k(lst->format, &chr, ap);
	else if (lst->format->convers == '}')
              	conv_color(lst, &chr, ap);
       	else if (lst->format->convers == 'p')
               	conv_p(lst, &chr, ap);
	else
		conv_percent(&chr);
}

void            fill_chr(t_lst *lst, t_chr *chr, va_list ap)
{
        while (lst)
        {
                while (chr && chr->str)
                        chr = chr->next;	
                if (ft_strchr("di", lst->format->convers))
                        conv_di(lst, &chr, ap);
		else if (ft_strchr("sckp}%", lst->format->convers))
			some_convers(lst, chr, ap);
		else if (ft_strchr("f", lst->format->convers)
				&& ft_strchr(lst->format->flag, 'L'))
			conv_llf(lst, &chr, ap);
		else if (ft_strchr("fHeEgG", lst->format->convers))
			conv_d_efgh(lst, &chr, ap);
                else if (ft_strchr("xXoub", lst->format->convers))
                        conv_xxoub(lst, &chr, ap);
                else
                        conv_invalid(&chr, lst->format, ap);
                lst = lst->next;
                chr = chr->next;
        }
}
