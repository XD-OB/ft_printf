#ifndef FT_PRINTF_H
# define FT_PRINTF_H


# include <stdio.h>


# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "libft/libft.h"
# include "structs.h"

# define ABS(x) (x < 0) ? -x : x

# define D_BIAS 1023
# define LD_BIAS 16383

# define MAX_D 	2047
# define MAX_LD 32767

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
void            conv_color(t_lst *lst, t_chr **mychr);
void            conv_c(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_s(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_p(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_di(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_lfh(t_lst *lst, t_chr **mychr, t_double db);
void		conv_ee(t_lst *lst, t_chr **mychr, t_double db);
void            conv_d_efgh(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_llf(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_percent(t_chr **mychr, t_lst *lst, va_list ap);
void            conv_di(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_xxoub(t_lst *lst, t_chr **mychr, va_list ap);
void            conv_invalid(t_chr **mychr, t_format *format, va_list ap);
void            zero_dbiouxx(char **str, t_format *fmt);
char            *flag_r(char c);
void            flag_star(t_format *format, va_list ap);
void            flag_zero(char **str, t_format *format);
void            flag_space(char **nbr, char *flag);
void            flag_plus(char **nbr, char conv);
void            flag_dash(char **nbr, int base);
void		flag_apostrophe(char **str, t_format *fmt);
int		flag_dollar(t_lst *lst);
char            *cut_str(char *str, int p1, int p2);
void            init_chr(t_chr **chr);
void            free_chr(t_chr *chr);
t_chr           *load_chr(char *format, t_lst *lst);
void            fill_chr(t_lst *lst, t_chr *chr, va_list ap);
int             put_chr(t_chr *chr);
int             put_chr_fd(int fd, t_chr *chr);
int             put_chr_nfd(int fd, size_t n, t_chr *chr);
int             pre_d_calc(t_double db, t_chr **mychr, t_lst *lst);
int             pre_ld_calc(t_ldouble db, t_chr **mychr, t_lst *lst);
long            int_exp(long bin_exp, int bias);
long            int_mants(long bin_mants, int bias);
char            *get_entier(long exp, long bin_mantis, int bias, t_format *format);
char            *get_fract(long exp, long bin_mantis, int bias, t_format *format);
char            *ft_fprecis(char *fract, int precis, int *carry);
char            *ft_fwidth(char *str, unsigned int size_str, t_format *format, unsigned int len_f);
char            *add_sign(char *str, int sign);
void            precis_o_udi(char **str, t_format *fmt, size_t nbr_len);

int	ft_printf(const char *format, ...);
int	ft_sprintf(char **str, const char *format, ...);
int	ft_vprintf(const char *format, va_list ap);
int	ft_dprintf(int fd, const char *format, ...);
int	ft_dnprintf(int fd, size_t n, const char *format, ...);
int	ft_snprintf(char **str, size_t n, const char *format, ...);


void    show_lst(t_lst *lst);
void     print_chr(t_chr *chr);


#endif
