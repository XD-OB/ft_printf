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
	}
	return (count_np);
}

void            conv_s(t_lst *lst, t_chr **mychr, va_list ap)
{
        int             count_np;
        int             i;
        int             j;
        int             len;
        int             len_s;
        char            *s;
        char            *str;

        flag_star(lst->format, ap);
	s = (flag_dollar(lst)) ? va_arg(*(lst->arglist), char*) : va_arg(ap, char*);
        if (!s)
        {
		(*mychr)->str = ft_strdup("(null)");
                (*mychr)->len = 6;
                return ;
        }
        len_s = (lst->format->precis != -1) ? lst->format->precis : (int)ft_strlen(s);
        len = (lst->format->width > len_s) ? lst->format->width : len_s;
        count_np = ft_countnp(s);
        if (!(str = (char*)malloc(sizeof(char) * (len + (count_np * 4) + 1))))
                return ;
        str[len + (count_np * 4)] = '\0';
        i = 0;
        if (!ft_strpbrk(lst->format->flag, "0-+") && len > len_s)
		while (i < len - len_s - (count_np * 4))
			str[i++] = ' ';
	j = -1;
	while (++j < len_s)
        {
		if (ft_isprint(s[j]) || !ft_strchr(lst->format->flag, 'r'))
			str[i] = s[j];
		else
		{
			ft_strcat(&str[i], flag_r(s[j]));
                       	i += 4;
                }
		i++;
        }
        (*mychr)->str = str;
        (*mychr)->len = ft_strlen(str);
}
