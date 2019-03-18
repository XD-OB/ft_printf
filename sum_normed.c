#include "libft.h"

/*	tab "a" indexes
**	len1 => 0; len2 => 1; i => 2; sum => 3; carry => 4
*/
char	*ft_strsum(char *s1, char *s2)
{
	char	*str;
	int		a[5];

	(ft_strlen(s1) > ft_strlen(s2)) ? ft_strswap(&s1, &s2) : 0;
	a[0] = ft_strlen(s1);
	a[1] = ft_strlen(s2);
	str = ft_strnew(0);
	a[4] = 0;
	a[2] = a[0];
	while (a[2]-- > 0)
	{
		a[3] = ((s1[a[2]] - '0') + (s2[a[2] + a[1] - a[0]] - '0') + a[4]);
		str = ft_str_pushback(str, a[3] % 10 + '0');
		a[4] = a[3] / 10;
	}
	a[2] = a[1] - a[0];
	while (a[2]-- > 0)
	{
		a[3] = ((s2[a[2]] - '0') + a[4]);
		str = ft_str_pushback(str, a[3] % 10 + '0');
		a[4] = a[3] / 10;
	}
	(a[4]) ? str = ft_str_pushback(str, a[4] + '0') : 0;
	str = ft_strrev(str);
	return (str); 
} 
