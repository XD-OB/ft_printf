#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;
	char		*s12;
	char		s2;

	s1 = "h\ni";
	s12 = "hi\t";
	s2 = 'h';
	ft_printf("%%");
	ft_putchar('\n');
	printf("%%");
	ft_putchar('\n');
	//printf("7string 1 %-012s string 2 %012s\n\n", "toto", "bonjour");
	//ft_printf("My hillifealing\n");
	return (0);
}
