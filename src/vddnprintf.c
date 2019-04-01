#include "ft_printf.h"

int             ft_vprintf(const char *format, va_list ap)
{
        t_chr           *mychr;
        t_lst           *lst;
        int             len;
        int             len_format;

        len = 0;
        len_format = 0;
        while (format[len_format])
                len_format++;
        lst = parse_format(ap, (char*)format);
        if (!lst)
        {
                put_spstr((char*)format);
                if (format[len_format - 1] == '%')
                        return (-1);
                return (ft_strlen(format));
        }
        if (!(mychr = load_chr((char*)format, lst)))
                return -1;
        fill_chr(lst, mychr, ap);
        print_lst(lst);
        len = put_chr(mychr);
        free_lst(lst);
        free_chr(mychr);
        va_end(ap);
        return (len);
}

int             ft_dprintf(int fd, const char *format, ...)
{
        t_chr           *mychr;
        t_lst           *lst;
        va_list         ap;
        int             len;
        int             len_format;

        len = 0;
        len_format = 0;
        while (format[len_format])
                len_format++;
        va_start(ap, format);
        lst = parse_format(ap, (char*)format);
        if (!lst)
        {
                put_spstr((char*)format);
                if (format[len_format - 1] == '%')
                        return (-1);
                return (ft_strlen(format));
        }
        if (!(mychr = load_chr((char*)format, lst)))
                return -1;
        fill_chr(lst, mychr, ap);
        print_lst(lst);
        len = put_chr_fd(fd, mychr);
        free_lst(lst);
        free_chr(mychr);
        va_end(ap);
        return (len);
}

int             ft_dnprintf(int fd, size_t n, const char *format, ...)
{
        t_chr           *mychr;
        t_lst           *lst;
        va_list         ap;
        int             len;
        int             len_format;

        len = 0;
        len_format = 0;
        while (format[len_format])
                len_format++;
        va_start(ap, format);
        lst = parse_format(ap, (char*)format);
        if (!lst)
        {
                put_spstr((char*)format);
                if (format[len_format - 1] == '%')
                        return (-1);
                return (ft_strlen(format));
        }
        if (!(mychr = load_chr((char*)format, lst)))
                return -1;
        fill_chr(lst, mychr, ap);
        print_lst(lst);
        len = put_chr_nfd(fd, n, mychr);
        free_lst(lst);
        free_chr(mychr);
        va_end(ap);
        return (len);
}
