#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

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

typedef struct		s_chr
{
	char		*str;
	int		len;
	struct s_chr	*next;
}			t_chr;

void	error(void);
int	is_format(char c);
int	is_postflag(char c);
int	is_preflag(char c);
int	is_valid(char *str);
int	lstlen(t_lst *lst);
void	put_spstr(char *str);
void	print_lst(t_lst *lst);
void	free_lst(t_lst *lst);
t_lst	*parse_format(char *str);
t_lst	*add_node(t_lst *head, t_lst *node);
int	ft_printf(const char *format, ...);

#endif
