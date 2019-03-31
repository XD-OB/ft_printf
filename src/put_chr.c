#include "ft_printf.h"

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

int             put_chr_fd(int fd, t_chr *chr)
{
        int     len;

        len = 0;
        while (chr)
        {
                ft_putstr_fd(chr->str, fd);
                len += chr->len;
                chr = chr->next;
        }
        return (len);
}

int             put_chr_nfd(int fd, size_t n, t_chr *chr)
{
	size_t	i;
       	size_t	len;

        len = 0;
        while (chr && len < n)
        {
		i = 0;
		while ((chr->str)[i] && len < n)
		{
                	ft_putchar_fd(chr->str[i], fd);
                	len++;
			i++;
		}
                chr = chr->next;
        }
        return (len);
}