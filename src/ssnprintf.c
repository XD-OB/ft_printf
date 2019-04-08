#include "ft_printf.h"

static unsigned int    get_chr_len(t_chr *mychr)
{
	unsigned int    len;

	len = 0;
	while (mychr)
	{
		len += mychr->len;
		mychr = mychr->next;
	}
	return (len);
}

static char		*str_chr(t_chr *mychr, unsigned int len_str)
{
	char            *str;
	unsigned int    i;
	unsigned int    j;

	str = (char*)malloc(sizeof(char) * len_str + 1);
	str[len_str] = '\0';
	i = 0;
	while (mychr && i < len_str)
	{
		j = 0;
		while (j < mychr->len && i < len_str)
		{
			str[i] = (mychr->str)[j];
			j++;
			i++;
		}
		mychr = mychr->next;
	}
	return (str);
}

int             	ft_sprintf(char **str, const char *format, ...)
{
	t_chr           *mychr;
	t_lst           *lst;
	va_list         ap;
	int    len;
	int    len_format;
	int		pflag;

	pflag = 0;
	len_format = 0;
	while (format[len_format++]);
	va_start(ap, format);
	lst = parse_format(ap, (char*)format, &pflag);
	if (!lst)
	{
		if (pflag == -1)
			return (0);
		put_spstr((char*)format);
		if (format[len_format - 1] == '%')
			return (-1);
		return (ft_strlen(format));
	}
	if (!(mychr = load_chr((char*)format, lst)))
		return -1;
	fill_chr(lst, mychr, ap);
	//print_lst(lst);
	len = get_chr_len(mychr);
	*str = str_chr(mychr, len);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len);
}

int             ft_snprintf(char **str, size_t n, const char *format, ...)
{
	t_chr		*mychr;
	t_lst		*lst;
	va_list		ap;
	size_t    	len;
	size_t		len_format;
	int			pflag;

	pflag = 0;
	len_format = 0;
	while (format[len_format++]);
	va_start(ap, format);
	lst = parse_format(ap, (char*)format, &pflag);
	if (!lst)
	{
		if (pflag == -1)
			return (0);
		put_spstr((char*)format);
		if (format[len_format - 1] == '%')
			return (-1);
		return (ft_strlen(format));
	}
	if (!(mychr = load_chr((char*)format, lst)))
		return -1;
	fill_chr(lst, mychr, ap);
	//print_lst(lst);
	len = get_chr_len(mychr);
	if (len > n)
		len = n;
	*str = str_chr(mychr, n);
	free_lst(lst);
	free_chr(mychr);
	va_end(ap);
	return (len);
}
