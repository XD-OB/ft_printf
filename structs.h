/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 03:44:15 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/17 17:19:39 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define GREEN  "\x1b[0;32m"
# define RED    "\x1b[0;31m"
# define YELLOW "\x1b[0;33m"
# define BLUE   "\x1b[0;34m"
# define PURPLE "\x1b[0;35m"
# define CYAN   "\x1b[0;36m"
# define B_GREEN  "\x1b[1;32m"
# define B_RED    "\x1b[1;31m"
# define B_YELLOW "\x1b[1;33m"
# define B_BLUE   "\x1b[1;34m"
# define B_PURPLE "\x1b[1;35m"
# define B_CYAN   "\x1b[1;36m"
# define EOC    "\x1b[0m"

typedef struct		s_64
{
	size_t			mantissa:52;
	long			exponent:11;
	long			sign:1;
}					t_64;

typedef struct		s_80
{
	size_t			mantissa:63;
	long			int_b:1;
	long			exponent:15;
	long			sign:1;
}					t_80;

typedef union		u_double
{
	t_64			zone;
	double			d;
}					t_double;

typedef union		u_ldouble
{
	t_80			zone;
	long double		ld;
}					t_ldouble;

typedef struct		s_format
{
	char			convers;
	char			*flag;
	long			precis;
	long			width;
	int				pos;
	int				argn;
}					t_format;

typedef struct		s_lst
{
	t_format		*format;
	va_list			*arglist;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_chr
{
	char			*str;
	unsigned int	len;
	struct s_chr	*next;
}					t_chr;

#endif
