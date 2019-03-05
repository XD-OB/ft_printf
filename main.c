#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;

	s1 = "hi";
	ft_printf("%#05x", 10);
	printf("\n%#05x\n", 10);
	//ft_printf("My hillifealing\n");
	ft_putchar('\n');
	return (0);
}
