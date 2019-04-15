#include <stdio.h>
#include "ft_printf.h"

static char		*ft_strzero(t_format *fmt, unsigned int *len)
{
	char		*res;

	*len = fmt->precis + 1;
	(*len > 1 || ft_strchr(fmt->flag, '#')) ? (*len)++ : 0;
	res = ft_strcnew(*len, '0');
	if (*len > 1)
		res[1] = '.';
	return (res);
}

static void		custom_nanf(t_format *fmt, char **str, unsigned int *len)
{
	unsigned int	i;
	unsigned int	j;
	char		*res;

	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		while (j < *len)
			res[i++] = (*str)[j++];
		*len = fmt->width;
		while (i < *len)
			res[i++] = ' ';
	}
	else
	{
		i = fmt->width;
		j = *len;
		while (j > 0)
			res[--i] = (*str)[--j];
		while (i > 0)
			res[--i] = ' ';
		*len = fmt->width;
	}
	free(*str);
	*str = res;
}

static void		custom_inff(t_format *fmt, char **str, unsigned int *len, int sign)
{
	unsigned int	i;
	unsigned int	j;
	char			*res;

	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		if (sign)
			res[i++] = '-';
		else if (ft_strchr(fmt->flag, '+'))
			res[i++] = '+';
		else if (ft_strchr(fmt->flag, ' '))
			res[i++] = ' ';
		while (j < *len)
			res[i++] = (*str)[j++];
		*len = fmt->width;
		while (i < *len)
			res[i++] = ' ';
	}
	else
	{
		i = fmt->width;
		j = *len;
		while (j > 0)
			res[--i] = (*str)[--j];
		if (sign)
			res[--i] = '-';
		else if (ft_strchr(fmt->flag, '+'))
			res[--i] = '+';
		else if (ft_strchr(fmt->flag, ' '))
			res[--i] = ' ';
		while (i > 0)
			res[--i] = ' ';
		*len = fmt->width;
	}
	free(*str);
	*str = res;
}

int             pre_d_calc(t_double db, t_chr **chr, t_lst *lst)
{
	char		*str;
	char		*tmp;
	unsigned int	len;

	if (!int_mants(db.zone.mantissa, D_BIAS) && !int_exp(db.zone.exponent, D_BIAS))
	{
		str = ft_strzero(lst->format, &len);
		(lst->format->width > (int)len) ? customize_f(lst->format, &str, &len, db.zone.sign)
			: add_sign_f(lst->format, &str, &len, db.zone.sign);
		if (ft_strchr("eE", lst->format->convers))
		{
			tmp = ft_strjoin(str, "e+00");
			free(str);
			str = tmp;
			len += 4;
		}
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	if (!int_mants(db.zone.mantissa, D_BIAS) && (int_exp(db.zone.exponent, D_BIAS) >= 2047))
	{
		str = ft_strdup("inf");
		len = 3;
		(lst->format->width > (int)len) ? custom_inff(lst->format, &str, &len, db.zone.sign)
			: add_sign_f(lst->format, &str, &len, db.zone.sign);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	if (int_mants(db.zone.mantissa, D_BIAS) && (int_exp(db.zone.exponent, D_BIAS) >= 2047))
	{
		str = ft_strdup("nan");
		len = 3;
		if (lst->format->width > (int)len)
			custom_nanf(lst->format, &str, &len);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	return (0);
}


int             pre_ld_calc(t_ldouble db, t_chr **chr, t_lst *lst)
{
	char		*str;
	unsigned int	len;

	if (!int_mants(db.zone.mantissa, LD_BIAS) && !int_exp(db.zone.exponent, LD_BIAS))
	{
		str = ft_strzero(lst->format, &len);
		(lst->format->width > (int)len) ? customize_f(lst->format, &str, &len, db.zone.sign)
			: add_sign_f(lst->format, &str, &len, db.zone.sign);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	if (!int_mants(db.zone.mantissa, LD_BIAS) && (int_exp(db.zone.exponent, LD_BIAS) >= 32767))
	{
		str = ft_strdup("inf");
		len = 3;
		(lst->format->width > (int)len) ? custom_inff(lst->format, &str, &len, db.zone.sign)
			: add_sign_f(lst->format, &str, &len, db.zone.sign);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	if (int_mants(db.zone.mantissa, LD_BIAS) && (int_exp(db.zone.exponent, LD_BIAS) >= 32767))
	{
		str = ft_strdup("nan");
		len = 3;
		if (lst->format->width > (int)len)
			custom_nanf(lst->format, &str, &len);
		(*chr)->str = str;
		(*chr)->len = len;
		return (1);
	}
	return (0);
}

long            int_exp(long bin_exp, int bias)
{
	long    ref;
	long	int_exp;

	int_exp = 0;
	ref = (bias == D_BIAS) ? 2048 : 32768;
	while (ref >>= 1)
		int_exp += (bin_exp & ref);
	return (int_exp);
}

long long		int_mants(long bin_mants, int bias)
{
	int				ref;
	long long    	int_mants;

	int_mants = 0;
	ref = (bias == D_BIAS) ? 53 : 63;
	while (--ref)
		int_mants += ((bin_mants >> ref) & 1);
	return (int_mants);
}
