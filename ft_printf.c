#include "ft_printf.h"

int	eqlst(t_lst *lst, va_list ap)
{
	int	len_lst;
	int	len_ap;

	len_lst = lstlen(lst);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	t_lst		*lst;
	va_list		ap;

	va_start(ap, format);
	lst = parse_format((char*)format);
	if (!eqlst(lst, ap))
		error();
	print_lst(lst);
	return (0);
}
