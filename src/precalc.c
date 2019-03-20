#include <stdio.h>
#include "ft_printf.h"

int             pre_d_calc(t_double db, t_chr **mychr)
{
	ft_printf("\nexponent: %b\n", db.zone.exponent);
	ft_printf("\nmantissa: %b\n", db.zone.mantissa);
        if (!int_mants(db.zone.mantissa, D_BIAS) && !int_exp(db.zone.exponent, D_BIAS))
        {
		ft_putstr("\n------- IM IN CAS1-------\n");
                (*mychr)->str = ft_strdup("0");
                (*mychr)->len = 1;
                return (1);
        }
        if (!int_mants(db.zone.mantissa, D_BIAS) && (int_exp(db.zone.exponent, D_BIAS) >= 2047))
        {
		ft_putstr("\n------- IM IN CAS2-------\n");
                (*mychr)->str = (db.zone.sign) ? ft_strdup("-inf") : ft_strdup("inf");
                (*mychr)->len = db.zone.sign + 3;
                return (1);
        }
        if (int_mants(db.zone.mantissa, D_BIAS) && (int_exp(db.zone.exponent, D_BIAS) >= 2047))
        {
		ft_putstr("\n------- IM IN CAS3-------\n");
                (*mychr)->str = (db.zone.sign) ? ft_strdup("-nan") : ft_strdup("nan");
                (*mychr)->len = db.zone.sign + 3;
                return (1);
        }
        return (0);
}


int             pre_ld_calc(t_ldouble db, t_chr **mychr)
{
        if (!int_mants(db.zone.mantissa, LD_BIAS) && !int_exp(db.zone.exponent, LD_BIAS))
        {
                (*mychr)->str = ft_strdup("0");
                (*mychr)->len = 1;
                return (1);
        }
        if (!int_mants(db.zone.mantissa, LD_BIAS) && (int_exp(db.zone.exponent, LD_BIAS) >= 32767))
        {
                (*mychr)->str = (db.zone.sign) ? ft_strdup("-inf") : ft_strdup("inf");
                (*mychr)->len = db.zone.sign + 3;
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

long            int_mants(long bin_mants, int bias)
{
        unsigned long	ref;
        long long    	int_mants;

        int_mants = 0;
        ref = (bias == D_BIAS) ? 2251799813685248 : 4611686018427387904;
        while (ref)
        {
                int_mants += (bin_mants & ref);
                ref >>= 1;
        }
        return (int_mants);
}
