#include "ft_printf.h"

static char                    *all_zero_p(char *nbr, int precis, int width)
{
        char    *res;
        int             len;
        int             len_nbr;
        int             i;
        int             j;

        len_nbr = (int)ft_strlen(nbr) - 2;
        len = precis;
        if (!width)
                len += 2;
        res = ft_strnew(len);
        i = 0;
        j = 2;
        res[i++] = '0';
       	res[i++] = 'x';
        while (i < (len - len_nbr))
                res[i++] = '0';
        while (i < len)
                res[i++] = nbr[j++];
        return (res);
}

static void                    precis_p(char **str, t_format *fmt, size_t nbr_len)
{
        int             i;
        int             j;
        int             len;
        char    *nbr;

        len = nbr_len - 2;
        if (ft_strchr(fmt->flag, '-'))
        {
                i = 0;
                j = 2;
                nbr = ft_strdup(*str);
             	(*str)[i++] = '0';
        	(*str)[i++] = 'x';
                while (i < fmt->precis - len + 2)
                        (*str)[i++] = '0';
                while(j < (int)nbr_len)
                        (*str)[i++] = nbr[j++];
                free(nbr);
        }
        else
        {
                i = ft_strlen(*str) - len - 1;
                j = fmt->precis - len;
                while (j-- && i >= 0)
                        (*str)[i--] = '0';
                (*str)[i--] = 'x';
                (*str)[i] = '0';
        }
}

static void		flag_plus_p(t_format *fmt, char **str)
{
	char	*res;
	int	i;

	if (!ft_strchr(fmt->flag, '+'))
		return ;
	if ((*str)[0] != ' ')
	{
		res = ft_strjoin("+", *str);
		free(*str);
		if (res[ft_strlen(res) - 1] == ' ')
			res[ft_strlen(res) - 1] = '\0';
		*str = res;
		return ;
	}
	i = 0;
	while ((*str)[i] == ' ')
		i++;
	(*str)[i - 1] = '+';
	return ;
}

void                    conv_p(t_lst *lst, t_chr **mychr, va_list ap)
{
        size_t          size;
        char            *str;
        char            *nbr;
        size_t          n;
        int                     i;

        flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ?
		(size_t)va_arg(*(lst->arglist), void*) : (size_t)va_arg(ap, void*);
        if (n == 0 && !lst->format->precis)
                (*mychr)->str = ft_strnew(0);
        else
        {
                nbr = ft_utoa_base(n, 16);
		flag_dash(&nbr, 16);
                flag_apostrophe(&nbr, lst->format);
                size = ft_max(ft_strlen(nbr), lst->format->width);
                if (!(str = ft_strnew(size)))
                        return ;
                if (ft_strchr(lst->format->flag, '-'))
                {
                        ft_strcpy(str, nbr);
                        i = ft_strlen(nbr);
                        while (i < (int)size)
                                str[i++] = ' ';
                }
                else
                {
                        i = 0;
                        while (i < (int)(size - ft_strlen(nbr) + 1))
                                str[i++] = ' ';
                        ft_strcpy(&str[--i], nbr);
                }
                if (lst->format->precis > 0 && lst->format->precis < lst->format->width)
                                precis_p(&str, lst->format, ft_strlen(nbr));
                if (lst->format->precis >= lst->format->width)
                        str = all_zero_p(nbr, lst->format->precis, 0);
                if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr) && !ft_strchr(lst->format->flag, '-'))
                        str = all_zero_p(nbr, lst->format->width, 1);
                (lst->format->convers == 'p') ? str = ft_strlowcase(str) : 0;
                (lst->format->convers == 'P') ? str = ft_strupcase(str) : 0;
		ft_putstr("\n ------str: ");
		ft_putendl(str);
		flag_plus_p(lst->format, &str);
                (*mychr)->str = str;
                free(nbr);
        }
        (*mychr)->len = ft_strlen(str);
}
