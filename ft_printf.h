#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "libft/libft.h"

# define GREEN	"\x1b[32m"
# define RED	"\x1b[31m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define PURPLE	"\x1b[35m"
# define CYAN	"\x1b[36m"
# define EOC	"\x1b[0m"

typedef struct		s_format
{
	char		convers;
	char		*flag;
	int		precis;
	int		width;
	int		pos;
}			t_format;

typedef struct		s_lst
{
	t_format	*format;
	struct s_lst	*next;
}			t_lst;

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
void            conv_k(t_format *format, t_chr **mychr, va_list ap);
void            conv_color(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_c(t_format *format, t_chr **mychr, va_list ap);
void            conv_s(t_format *format, t_chr **mychr, va_list ap);
void            conv_p(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_percent(t_chr **mychr);
void            conv_di(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_xxoub(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_s(t_format *format, t_chr **mychr, va_list ap);
void            conv_invalid(t_chr **mychr, t_format *format, va_list ap);
char            *flag_r(char c);
void            flag_star(t_format *format, va_list ap);
void            flag_zero(char **str, t_format *format);
void            flag_space(char **nbr, char *flag);
void            flag_plus(char **nbr);
void            flag_dash(char **nbr, int base);
char            *cut_str(char *str, int p1, int p2);
void            init_chr(t_chr **chr);
void            free_chr(t_chr *chr);
t_chr           *load_chr(char *format, t_lst *lst);
void            fill_chr(t_lst *lst, t_chr *chr, va_list ap);
int             put_chr(t_chr *chr);

int	ft_printf(const char *format, ...);

void    show_lst(t_lst *lst);
void     print_chr(t_chr *chr);


#endif
