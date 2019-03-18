#include "libft.h"

char	*ft_strsum(char *str1, char *str2) 
{ 
	char	*str;
	int		len1;
	int		len2;
	int		diff;
	int		i;
	int		sum;
	int		carry;

	if (ft_strlen(str1) > ft_strlen(str2)) 
		ft_strswap(&str1, &str2);

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	
	str = ft_strnew(0);

	diff = len2 - len1;

	carry = 0; 

	for (i=len1-1; i>=0; i--) 
	{ 
		sum = ((str1[i]-'0') + (str2[i+diff]-'0') + carry); 
		str = ft_str_pushback(str, sum % 10 + '0'); 
		carry = sum / 10; 
	} 

	for (i=len2-len1-1; i>=0; i--) 
	{ 
		sum = ((str2[i] - '0') + carry); 
		str = ft_str_pushback(str, sum % 10 + '0');
		carry = sum / 10;
	} 

	if (carry) 
		str = ft_str_pushback(str, carry + '0'); 

	str = ft_strrev(str);

	return str; 
} 
