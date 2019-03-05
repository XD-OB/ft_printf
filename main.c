#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;

	s1 = "hi";
	//ft_printf("%0.2p", &s1);
	printf("\n%0.2p\n", &s1);
	//ft_printf("My hillifealing\n");
	return (0);
}
