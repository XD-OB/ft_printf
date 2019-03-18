#include <stdlib.h>

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = '\0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_push_back(char *str, char c)
{
	char	*new_str;
	int		newlen;
	int		len;

	len = ft_strlen(str);
	newlen = len + 1;
	new_str = ft_strnew(newlen);
	new_str[len] = c;
	while (len--)
		new_str[len] = str[len];
	free(str);
	return (new_str);
}

char    *ft_strrev(char *str)
{
	char tmp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
		j++;
	j--;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

char	*sum_str(char *str1, char *str2) 
{ 
	char	*str;
	int		len1;
	int		len2;
	int		diff;
	int		i;
	int		sum;
	int		carry;

	if (ft_strlen(str1) > ft_strlen(str2)) 
		ft_swap(&str1, &str2);

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	
	str = ft_strnew(0);

	diff = len2 - len1;

	carry = 0; 

	for (i=len1-1; i>=0; i--) 
	{ 
		sum = ((str1[i]-'0') + (str2[i+diff]-'0') + carry); 
		str = ft_push_back(str, sum % 10 + '0'); 
		carry = sum / 10; 
	} 

	for (i=len2-len1-1; i>=0; i--) 
	{ 
		sum = ((str2[i] - '0') + carry); 
		str = ft_push_back(str, sum % 10 + '0');
		carry = sum / 10;
	} 

	if (carry) 
		str = ft_push_back(str, carry + '0'); 

	str = ft_strrev(str);

	return str; 
} 
