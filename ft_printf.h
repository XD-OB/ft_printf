#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct			s_format
{
	char				convers;
	char				*flag;
	int					precis;
	int					width;
	int					pos;
}						t_format;

typedef struct			s_list
{
	t_format			*format;
	struct s_list		next;
}						t_list;

#endif
