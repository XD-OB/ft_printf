#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;
	char		*s12;
	char		s2;
	char		*str;

	s1 = "hi there";
	s12 = "hi";
	s2 = 'h';
	str = "This is a test text";
	ft_printf("flaot:%A", 35296.998);
	printf("\n");
	printf("flaot:%A", 35296.998);
	printf("\n");
	//ft_printf("Le fichier %{cyanmnnnnnnnnnnnnnnnn} %s %{eoc} contient : %{red}%s%{eoc}", s1, str);
	//ft_putchar('\n');
	//printf("7string 1 %-012s string 2 %012s\n\n", "toto", "bonjour");
	//ft_printf("My hillifealing\n");
	return (0);
}
