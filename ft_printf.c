#include "ft_printf.h"

void	delist(t_lst *lst)
{
	t_lst	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->format);
		free(lst);
		lst = next;
	}
}

int	eq_lst(t_lst *lst, va_list ap)
{
	int	len_lst;
	int	len_ap;

	len_ap = 1;
	len_lst = lstlen(lst);
	while (va_arg(ap, void*))
		len_ap++;
	ft_putnbr(len_ap);
	ft_putchar('\n');
	ft_putnbr(len_lst);
	ft_putchar('\n');
	va_end(ap);
	if (len_ap != len_lst)
	{
		delist(lst);
		error();
	}
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
	return (0);
}
