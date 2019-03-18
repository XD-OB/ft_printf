#include "libft.h"

char	*ft_str_pushback(char *str, char c)
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
