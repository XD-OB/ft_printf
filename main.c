#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;

	s1 = "hi";
	ft_printf("%-5d", 50);
	printf("\n%-5d\n", 50);
	//ft_printf("My hillifealing\n");
	return (0);
}
