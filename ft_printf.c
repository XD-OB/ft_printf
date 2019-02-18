#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
	t_list		**lst;
	var_list	ap;

	*lst = NULL;
	lst = parse_format((char*)format);
}
