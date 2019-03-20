#include "./ft_printf.h"
#include <stdio.h>

int	main(void)
{
	char		*s1;
	char		*s12;
	char		s2;
	char		*str;
	char		*zaza;
	char		*zaza2;

	s1 = "hi there";
	s12 = "hi";
	s2 = 'h';
	str = "This is a test text";
	ft_sprintf(zaza, "flaot:%g", 0.314);
	printf("%s", zaza);
	//sprintf(zaza2, "flaot:%g", 0.314);
	//printf("%s", zaza2);
	printf("\n");
	printf("flaot:%g", 0.314);
	printf("\n");
	//ft_printf("Le fichier %{cyanmnnnnnnnnnnnnnnnn} %s %{eoc} contient : %{red}%s%{eoc}", s1, str);
	//ft_putchar('\n');
	//printf("7string 1 %-012s string 2 %012s\n\n", "toto", "bonjour");
	//ft_printf("My hillifealing\n");
	return (0);
}
