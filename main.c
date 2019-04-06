#include "./ft_printf.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(void)
{
	char		*s1;
	char		*s12;
	char		*str;
	char		*zaza;
	char		c;

	s1 = "hi there";
	s12 = "hi";
	c = 'h';
	str = "This is a test text";
	ft_printf("%.40e", 0.000000000000000000000000000000000000014);
	printf("\n");
	printf("%.40e", 0.000000000000000000000000000000000000014);
	printf("\n");
	//printf("flaot:%g", 0.314);
	//printf("\n");
	//ft_printf("Le fichier %{cyanmnnnnnnnnnnnnnnnn} %s %{eoc} contient : %{red}%s%{eoc}", s1, str);
	//ft_putchar('\n');
	//printf("7string 1 %-012s string 2 %012s\n\n", "toto", "bonjour");
	//ft_printf("My hillifealing\n");
	return (0);
}
