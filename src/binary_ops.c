#include "../ft_printf.h"

int	bin_add(int a, int b)
{
	int	res;
	int	carry;
	int	x;
	int	i;

	res = 0;
	x = 1;
	i = 8;
	carry = 0;
	while (--i)
	{
		carry = 0;
		ft_putstr("\n a & x: ");
		ft_putnbr(a & x);
		ft_putstr("\n b & x: ");
		ft_putnbr(b & x);
		ft_putchar('\n');
		if ((a & x) && (b & x))
			carry = x << 1;
		else if ((a & x) || (b & x))
			res = (res << 1) | 0x1;
		ft_putstr("\n carry: ");
		ft_putnbr(carry);
		ft_putchar('\n');
		x <<= 1;
		if (carry)
			res = (res << 1) | carry;
		ft_putstr("\n res: ");
		ft_putnbr(res);
		ft_putchar('\n');
	}
	return (res);
}

int		main(void)
{
	int	n1 = 3;
	int	n2 = 1;

	ft_printf("n1   : %b\n", n1);
	ft_printf("n2   : %b\n", n2);
	ft_printf("n1+n1: %b\n", bin_add(n2, n1));
	return (0);
}
