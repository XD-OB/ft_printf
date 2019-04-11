#include "libft.h"

void	ft_printhex(int n)
{
	int	c;

	if (n >= 16)
		ft_printhex(n / 16);
	c = (n % 16) + ((n % 16 < 10) ? '0' : 'a' - 10);
	ft_putchar(c);
}
