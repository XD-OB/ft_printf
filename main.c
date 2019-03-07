#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;
	char		s2;

	s1 = "hi";
	s2 = 'h';
	ft_printf("%{blue}OUSSAMA %{yellow}%d dh%{eoc}\n", 10);
	printf("7string 1 %-012s string 2 %012s\n\n", "toto", "bonjour");
	//ft_printf("My hillifealing\n");
	return (0);
}
