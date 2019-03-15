#include "ft_printf.h"

void            conv_c(t_lst *lst, t_chr **mychr, va_list ap)
{
        int     i;
        int     len;
        char    *str;

        i = -1;
        flag_star(lst->format, ap);
        len = lst->format->width;
        if (lst->format->width < 2 || ft_strpbrk(lst->format->flag, "+-0#"))
                len = 1;
        str = (char*)malloc(sizeof(char) * (len + 1));
        str[len] = '\0';
        while (++i < len - 1)
                str[i] = ' ';
	if (flag_dollar(lst))
        	str[i] = (char)va_arg(*(lst->arglist), int);
	else
		str[i] = (char)va_arg(ap, int);
        (*mychr)->str = str;
        (*mychr)->len = len;
}

static int	ft_countnp(char *s)
{
	int	i;
	int	count_np;

	i = -1;
	count_np = 0;
	while (s[++i])
	{
		if ((s[i] >= 0 && s[i] < 32) || s[i] == 127)
			count_np++;
		i++;
	}
	return (count_np);
}

void            conv_s(t_lst *lst, t_chr **mychr, va_list ap)
{
        int             count_np;
        int             i;
        int             len;
        int             len_s;
        char            *s;
        char            *str;

        flag_star(lst->format, ap);
	if (flag_dollar(lst))
		s = va_arg(*(lst->arglist), char*);
	else
		s = va_arg(ap, char*);
        if (!s)
        {
		(*mychr)->str = ft_strdup("(null)");
                (*mychr)->len = 6;
                return ;
        }
        len_s = (lst->format->precis != -1) ? lst->format->precis : (int)ft_strlen(s);
        len = len_s;
        (lst->format->width > len) ? len = lst->format->width : 0;
        count_np = ft_countnp(s);
        if (!(str = (char*)malloc(sizeof(char) * (len + (count_np * 4) + 1))))
                return ;
        str[len + (count_np * 4)] = '\0';
        i = -1;
        if ((ft_strchr(lst->format->flag, '0') && !ft_strchr(lst->format->flag, '-'))
                        || !ft_strpbrk(lst->format->flag, "0-+"))
        {
                if (len == lst->format->width)
                        while (++i < len - len_s)
                                str[i] = ' ';
                i--;
                while (++i < len)
                {
                        if (ft_isprint(s[i - len + len_s]) || !ft_strchr(lst->format->flag, 'r'))
                                str[i] = s[i - len + len_s];
                        else
                        {
                                ft_strcat(&str[i], flag_r(s[i - len + len_s]));
                                //i += 5;
                        }
                }
        }
        else
        {
                while (++i < len_s)
                {
                        if (ft_isprint(s[i]) || !ft_strchr(lst->format->flag, 'r'))
                                str[i] = s[i];
                        else
                        {
                                ft_strcat(&str[i], flag_r(s[i]));
                                //i += 5;
                        }
                }
                if (len == lst->format->width)
                        while (i < len)
                                str[i++] = ' ';
        }
        (*mychr)->str = str;
        (*mychr)->len = len;
}
