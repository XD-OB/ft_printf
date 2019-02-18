#include "ft_printf.h"

void	print_lst(t_lst *lst)
{
	while (lst)
	{
		ft_putendl(lst->format->flag);
		ft_putnbr(lst->format->width);
		ft_putchar('\n');
		ft_putnbr(lst->format->precis);
		ft_putchar(lst->format->convers);
		lst = lst->next;
	}
	ft_putchar('\n');
}

int ft_printf(const char *format, ...)
{
	t_lst		**lst;
	va_list	ap;

	lst = (t_lst**)malloc(sizeof(t_lst*));
	*lst = (t_lst*)malloc(sizeof(t_lst));
	(*lst)->format = (t_format*)malloc(sizeof(t_format));
	parse_format((char*)format, lst);
	//print_lst(*lst);
	return (0);
}

int		main(void)
{
	ft_printf("%s");
	return (0);
}
