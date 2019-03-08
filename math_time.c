#include <stdio.h>

int		main()
{
	long int s = 8640000;
	long int nbr_days = s / 86400 + 719468;
	long int era = (nbr_days >= 0 ? nbr_days : nbr_days - 146096) / 146097;
	unsigned long int doe = (unsigned long int)(nbr_days - era * 146097);
	unsigned long int yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;
	long int y = (long int)(yoe) + era * 400;
	unsigned long int doy = doe - (365*yoe + yoe/4 - yoe/100);
	unsigned long int mp = (5*doy + 2)/153;
	unsigned long int d = doy - (153*mp+2)/5 + 1;
	unsigned long int m = mp + (mp < 10 ? 3 : -9);
	y += (m <= 2);
	printf("%ld/%ld/%ld\n", m, d, y);
	return (0);



}
