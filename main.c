#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;

	s1 = "hi";
	ft_printf("%hd", 200);
	printf("\n%hd\n", 200);
	return (0);
}
