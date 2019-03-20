#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "libft/libft.h"

# define D_BIAS 1023
# define LD_BIAS 16383

# define MAX_D 	2047
# define MAX_LD 32767

# define GREEN	"\x1b[32m"
# define RED	"\x1b[31m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define PURPLE	"\x1b[35m"
# define CYAN	"\x1b[36m"
# define EOC	"\x1b[0m"

typedef struct			s_64
{
	size_t		mantissa:52;
	long			exponent:11;
	long			sign:1;
}				t_64;

typedef struct		s_80
{
	size_t		mantissa:63;
	long		int_b:1;
	long		exponent:15;
	long		sign:1;
}			t_80;

typedef union		u_double
{
	t_64		zone;
	double		d;
}			t_double;

typedef union		u_ldouble
{
	t_80		zone;
	long double	ld;
}			t_ldouble;

typedef struct		s_format
{
	char		convers;
	char		*flag;
	int		precis;
	int		width;
	int		pos;
	int		argn;
}			t_format;

typedef struct		s_lst
{
	t_format	*format;
	va_list		*arglist;
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
t_lst	*parse_format(va_list ap, char *str);
t_lst	*add_node(t_lst *head, t_lst *node);
void            conv_k(t_format *format, t_chr **mychr, va_list ap);
void            conv_color(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_c(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_s(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_p(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_d_efgh(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_llf(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_percent(t_chr **mychr);
void            conv_di(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_xxoub(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_invalid(t_chr **mychr, t_format *format, va_list ap);
char            *flag_r(char c);
void            flag_star(t_format *format, va_list ap);
void            flag_zero(char **str, t_format *format);
void            flag_space(char **nbr, char *flag);
void            flag_plus(char **nbr);
void            flag_dash(char **nbr, int base);
void		flag_apostrophe(char **str, t_format *fmt);
int		flag_dollar(t_lst *lst);
char            *cut_str(char *str, int p1, int p2);
void            init_chr(t_chr **chr);
void            free_chr(t_chr *chr);
t_chr           *load_chr(char *format, t_lst *lst);
void            fill_chr(t_lst *lst, t_chr *chr, va_list ap);
int             put_chr(t_chr *chr);
int             pre_d_calc(t_double db, t_chr **mychr);
int             pre_ld_calc(t_ldouble db, t_chr **mychr);
long            int_exp(long bin_exp, int bias);
long            int_mants(long bin_mants, int bias);

int	ft_printf(const char *format, ...);

void    show_lst(t_lst *lst);
void     print_chr(t_chr *chr);


#endif
