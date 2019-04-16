#include "libft.h"

#define MAX 100000 

static int	multiply(int x, int *res, int res_size) { 

	int		carry;
	int		i;

	i = 0;
	carry = 0;
	while (i < res_size)
	{ 
		int prod = res[i] * x + carry; 
		res[i] = prod % 10; 
		carry = prod / 10;
		i++;
	} 
	while (carry)
	{ 
		res[res_size] = carry % 10; 
		carry = carry / 10; 
		res_size++; 
	} 
	return (res_size); 
} 

char	*ft_strpower(int x, int n)
{ 
	char	*s;
	int 	res[MAX]; 
	int 	res_size; 
	int 	temp; 
	int		i;

	if (n == 0)
		return (ft_strdup("1")); 
	res_size = 0;
	temp = x;
	s = ft_strnew(0);
	while (temp) 
	{ 
		res[res_size++] = temp % 10; 
		temp = temp / 10; 
	}
	i = 2;  
	while (i++ <= n) 
		res_size = multiply(x, res, res_size);
	//s = ft_strnew(res_size);
	i = res_size - 1; 
	while (i >= 0) 
	{
		//s[i] = res[i] + 48;
		s = ft_str_pushback(s, (res[i] + 48));
		i--;
	}
	return (s);
} 
