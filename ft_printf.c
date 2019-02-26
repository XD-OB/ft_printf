#include "ft_printf.h"

int	eq_lst(t_lst *lst, va_list ap)
{
	int	len_lst;
	int	len_ap;

	len_ap = 1;
	len_lst = lstlen(lst);
	while (va_arg(ap, void*))
		len_ap++;
	va_end(ap);
	if (len_ap != len_lst)
		frerrorlst(lst);
}

void	engine(t_lst *lst, va_list ap)
{
}

int	ft_printf(const char *format, ...)
{
	t_lst		*lst;
	va_list		ap;
	int		len = 1;

	va_start(ap, format);
	lst = parse_format((char*)format);
	eq_lst(lst, ap);
	print_lst(lst);
	va_start(ap, format);
	engine(lst, ap);
	return (0);
}
