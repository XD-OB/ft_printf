#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;
	char		s2;

	s1 = "hi";
	s2 = 'h';
	ft_printf("Oussama %20p\n", &s1);
	printf("Oussama %20p\n", &s1);
	//ft_printf("My hillifealing\n");
	return (0);
}
