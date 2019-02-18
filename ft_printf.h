#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft/libft.h"

typedef struct			s_format
{
	char				convers;
	char				*flag;
	int					precis;
	int					width;
	int					pos;
}						t_format;

typedef struct			s_lst
{
	t_format			*format;
	struct s_lst		*next;
}						t_lst;

void	parse_format(char *str, t_lst **lst);

#endif
