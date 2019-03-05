#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;

	s1 = "hi";
	ft_printf("%shiwork%d", s1, 20);
	printf("\n%shiwork%d\n", s1, 20);
	//ft_printf("My hillifealing\n");
	return (0);
}
