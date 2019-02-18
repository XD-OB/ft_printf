#include "ft_printf.h"

void	print_list(t_list *lst)
{
	while (lst)
	{
		ft_putendl(lst->format.flag);
		ft_putnbr(lst->format.width);
		ft_putchar('\n');
		ft_putnbr(lst->format.precis);
		ft_putendl(lst->format.convers);
		lst = lst->next;
	}
	ft_putstr('\n');
}

int ft_printf(const char *format, ...)
{
	t_list		**lst;
	var_list	ap;

	*lst = NULL;
	*lst = parse_format((char*)format);
	print_list(*lst);
}
