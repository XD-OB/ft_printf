#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;

	s1 = "hi";
	ft_printf("%d %m", 50);
	printf("\n%d %m\n", 50);
	//ft_printf("My hillifealing\n");
	return (0);
}
