#include "libft.h"

static char		*ft_put_into_s(int *result, int n1, int n2)
{
	int		i;
	char	*s;

	i = n1 + n2 - 1;
	while (i>=0 && result[i] == 0) 
		i--;
	if (i == -1)
	{
		free(result);
		return (ft_strcnew(1, '0'));
	}
	s = ft_strnew(0); 
	while (i >= 0) 
		s = ft_str_pushback(s, result[i--] + '0');
	free(result);
	return (s);
}

char	*ft_strmult(char *num1, char *num2) 
{
	t_mult	m;

	if (!(m.n1 = ft_strlen(num1)) || !(m.n2 = ft_strlen(num2)))
		return (ft_strcnew(1, '0'));
	m.result = (int*)ft_memalloc(sizeof(int) * (m.n1 + m.n2));
	m.i_n1 = 0;
	m.i_n2 = 0; 
	m.i = m.n1;
	while (m.i-- > 0) 
	{ 
		m.carry = 0; 
		m.i_n2 = 0;
		m.j = m.n2; 
		while (m.j-- > 0) 
		{ 
			m.sum = (num1[m.i] - 48) * (num2[m.j] - 48) + m.result[m.i_n1 + m.i_n2] + m.carry; 
			m.carry = m.sum / 10; 
			m.result[m.i_n1 + m.i_n2] = m.sum % 10; 
			m.i_n2++; 
		} 
		(m.carry > 0) ? m.result[m.i_n1 + m.i_n2] += m.carry : 0;
		m.i_n1++; 
	} 
	m.s = ft_put_into_s(m.result, m.n1, m.n2);
	return (m.s);
} 
