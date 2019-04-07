#include <stdio.h>
#include "ft_printf.h"

static char		*ft_strzero(t_lst *lst, int sign)
{
	char		*entier;
	char		*fract;
	char		*res;

	fract = ft_strcnew(lst->format->precis, '0');
	if (lst->format->width > lst->format->precis + 1)
	{
		entier = ft_strcnew((lst->format->width - lst->format->precis - 1), (ft_strchr(lst->format->flag, '0')) ? '0' : ' ');
		entier[lst->format->width - lst->format->precis - 2] = '0';
	}
	else
		entier = ft_strcnew(1, '0');
	if (sign == 1 || ft_strchr(lst->format->flag, '+') || ft_strchr(lst->format->flag, ' '))
	{
		if (ft_strlen(entier) == 1)
		{
			free(entier);
			entier = ft_strcnew(2, '0');
		}
		entier[0] = (sign == 1) ? '-' : ((ft_strchr(lst->format->flag, '+')) ? '+' : ' ');
	}
	res = ft_strnew(ft_strlen(entier) + lst->format->precis + 1);
	ft_strcat(res, entier);
	ft_strcat(res, ".");
	ft_strcat(res, fract);
	free(entier);
	free(fract);
	return (res);
}

int             pre_d_calc(t_double db, t_chr **mychr, t_lst *lst)
{
        if (!int_mants(db.zone.mantissa, D_BIAS) && !int_exp(db.zone.exponent, D_BIAS))
        {
                (*mychr)->str = ft_strzero(lst, db.zone.sign);
                (*mychr)->len = ft_strlen((*mychr)->str);
                return (1);
        }
        if (!int_mants(db.zone.mantissa, D_BIAS) && (int_exp(db.zone.exponent, D_BIAS) >= 2047))
        {
                (*mychr)->str = (db.zone.sign) ? ft_strdup("-inf") : ft_strdup("inf");
                (*mychr)->len = (db.zone.sign) ? 4 : 3;
                return (1);
        }
        if (int_mants(db.zone.mantissa, D_BIAS) && (int_exp(db.zone.exponent, D_BIAS) >= 2047))
        {
                (*mychr)->str = ft_strdup("nan");
                (*mychr)->len = 3;
                return (1);
        }
        return (0);
}


int             pre_ld_calc(t_ldouble db, t_chr **mychr, t_lst *lst)
{
        if (!int_mants(db.zone.mantissa, LD_BIAS) && !int_exp(db.zone.exponent, LD_BIAS))
        {
                (*mychr)->str = ft_strzero(lst, db.zone.sign);
                (*mychr)->len = ft_strlen((*mychr)->str);
                return (1);
        }
        if (!int_mants(db.zone.mantissa, LD_BIAS) && (int_exp(db.zone.exponent, LD_BIAS) >= 32767))
        {
                (*mychr)->str = (db.zone.sign) ? ft_strdup("-inf") : ft_strdup("inf");
                (*mychr)->len = (db.zone.sign) ? 4 : 3;
                return (1);
        }
        if (int_mants(db.zone.mantissa, LD_BIAS) && (int_exp(db.zone.exponent, LD_BIAS) >= 32767))
        {
                (*mychr)->str = ft_strdup("nan");
                (*mychr)->len = 3;
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
