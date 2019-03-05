#include "ft_printf.h"

void	error(void)
{
	write(1, "Invalid format\n", 15);
	exit(-1);
}

static int	is_repeat(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	if (count > 1)
		return (1);
	return (0);
}

static int	not_repstr(char *str, char c)
{
	int	countc;
	int	countcc;

	countc = 0;
	countcc = 0;
	while (*str)
	{
		if (*str == c)
		{
			if (*(str + 1) == c)
			{
				if (*(str + 2) == c)
					return (0);
				countcc++;
				str++;
			}
			else
				countc++;
		}
		str++;
	}
	if (countc == 0 && countcc == 1)
		return (countcc);
	if (countcc == 0 && countc == 1)
		return (countc);
	if (countcc == 0 && countc == 0)
		return (-1);
	return (0);
}

int		is_valid(char *str)
{
	int	i;
	char	*ndbl;

	i = 0;
	ndbl = " 0+-#'*L$";
	while (ndbl[i])
		if (is_repeat(str, ndbl[i++]))
			return (0);
	if (!not_repstr(str, 'h') || !not_repstr(str, 'l'))
		return (0);
	if (not_repstr(str, 'h') != -1 && not_repstr(str, 'l') != -1)
		return (0);
	if ((not_repstr(str, 'h') != -1 || not_repstr(str, 'l') != -1) && ft_strchr(str, 'L'))
		return (0);
	return (1);
}
