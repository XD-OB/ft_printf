#include "./ft_printf.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <float.h>

void	_vfunction(const char *format, ...)
{
	va_list	ap;
	
	va_start(ap, format);
	ft_vprintf(format, ap);
}

int	main(void)
{
	char		*str;
	char		*s;
	int			fd;

	str = "This is a test text";

	//ft_printf("%lx|%-lx|%#lx|%0lx", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	//printf("\n");
	//printf("%lx|%-lx|%#lx|%0lx", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	//printf("\n");
	//ft_printf("TEST2---%.2x", 5427);
	//printf("\n");
	//printf("ORIG ---%.2x", 5427);
	//printf("\n");
	//ft_printf("TEST3---@moulitest: %.x %.0x", 0, 0);
	//printf("\n");
	//printf("ORIG ---@moulitest: %.x %.0x", 0, 0);
	//printf("\n");
	//ft_printf("TEST4---@moulitest: %5.x", 0);
	//printf("\n");
	//printf("ORIG ---@moulitest: %5.x", 0);
	//printf("\n");
	//ft_printf("TEST4---@moulitest: %5.0x", 0);
	//printf("\n");
	//printf("ORIG ---@moulitest: %5.0x", 0);
	//printf("\n");
	//ft_printf("TEST5---%s%s%s%s%s", "this", "is", "a", "multi", "string");	
	//printf("\n");
	//printf("ORIG ---%s%s%s%s%s", "this", "is", "a", "multi", "string");	
	//printf("\n");
	//ft_printf("TEST6---%.2c", NULL);
	//printf("\n");
	//printf("ORIG ---%.2c", NULL);
	//printf("\n");
	//ft_printf("TEST7---@moulitest: %c", 0);
	//printf("\n");
	//printf("ORIG ---@moulitest: %c", 0);
	//printf("\n");
	//ft_printf("TEST8---%2c", 0);
	//printf("\n");
	//printf("ORIG ---%2c", 0);
	//printf("\n");
	//ft_printf("TEST9---null %c and text", 0);
	//printf("\n");
	//printf("ORIG ---null %c and text", 0);
	//printf("\n");
	//ft_printf("TEST10---% c", 0);
	//printf("\n");
	//printf("ORIG ---% c", 0);
	//printf("\n");
	//ft_printf("TEST11---@moulitest: %.o %.0o", 0, 0);
	//printf("\n");
	//printf("ORIG  ---@moulitest: %.o %.0o", 0, 0);
	//printf("\n");
	//ft_printf("TEST12---@moulitest: %5.o %5.0o", 0, 0);
	//printf("\n");
	//printf("ORIG  ---@moulitest: %5.o %5.0o", 0, 0);
	//printf("\n");
	//ft_printf("TEST13---@moulitest: %#.o %#.0o", 0, 0);
	//printf("\n");
	//printf("ORIG  ---@moulitest: %#.o %#.0o", 0, 0);
	//printf("\n");
	//ft_printf("TEST14---% d", -42);
	//printf("\n");
	//printf("ORIG  ---% d", -42);
	//printf("\n");
	//ft_printf("TEST15---%+d", 0);
	//printf("\n");
	//printf("ORIG  ---%+d", 0);
	//printf("\n");
	//ft_printf("TEST16---%0+5d", 42);
	//printf("\n");
	//printf("ORIG  ---%0+5d", 42);
	//printf("\n");
	//ft_printf("TEST17---%lld", -92233720368547758);
	//printf("\n");
	//printf("ORIG  ---%lld", -92233720368547758);
	//printf("\n");
	//ft_printf("TEST18---%03.2d", 0);
	//printf("\n");
	//printf("ORIG  ---%03.2d", 0);
	//printf("\n");
	//ft_printf("TEST19---%03.2d", 1);
	//printf("\n");
	//printf("ORIG  ---%03.2d", 1);
	//printf("\n");
	//ft_printf("TEST20---@moulitest: %.10d", -42);
	//printf("\n");
	//printf("ORIG  ---@moulitest: %.10d", -42);
	//printf("\n");
	//ft_printf("TEST21---@moulitest: %.d %d", 0, 0);
	//printf("\n");
	//printf("ORIG  ---@moulitest: %.d %d", 0, 0);
	//printf("\n");
	//ft_printf("TEST22---@moulitest: %05.2d %5.0d", 4523, 4523);
	//printf("\n");
	//printf("ORIG  ---@moulitest: %05.2d %5.0d", 4523, 4523);
	//printf("\n");
	//ft_printf("%%");
	//printf("\n");
	//printf("%%");
	//printf("\n");
	//ft_printf("%7.5d", 5427);
	//printf("\n");
	//printf("%7.5d", 5427);
	//printf("\n");
	//ft_printf("%+d", 42);
	//printf("\n");
	//printf("%+d", 42);
	//printf("\n");
	//ft_printf("m%#.9od\nee", 123456789);
	//printf("\n");
	//printf("m%#.9od\nee", 123456789);
	//printf("\n");
	//ft_printf("toto %###.0o%#.o et %#.1o !", 0, 0, 0);
	//printf("\n");
	//printf("toto %###.0o%#.o et %#.1o !", 0, 0, 0);
	//printf("\n");
	//ft_printf("toto %0##0.4X%#4.2xet c'est fini \n", 0x037a, 0x9e);
	//printf("\n");
	//printf("toto %0##0.4X%#4.2xet c'est fini \n", 0x037a, 0x9e);
	//printf("\n");
	//ft_printf("TEST : %.2s", NULL);
	//printf("\n");
	//printf("TEST : %.2s", NULL);
	//printf("\n");
	//ft_printf("TEST : %20.10s", NULL);
	//printf("\n");
	//printf("TEST : %20.10s", NULL);
	//printf("\n");
	//ft_printf("TEST : %020.10s", NULL);
	//printf("\n");
	//printf("TEST : %020.10s", NULL);
	//printf("\n");
	//ft_printf("TEST : %-020.10s", NULL);
	//printf("\n");
	//printf("TEST : %-020.10s", NULL);
	//printf("\n");
	//ft_printf("Coucou %.0s\n%s%---12s", "hi", "coco", NULL);
	//printf("\n");
	//printf("Coucou %.0s\n%s%---12s", "hi", "coco", NULL);
	//printf("\n");
	//ft_printf("TEST : u%4.2ss %-1.s", "coco", NULL);
	//printf("\n");
	//printf("TEST : u%4.2ss %-1.s", "coco", NULL);
	//printf("\n");
	//ft_printf("%1.4s et %-6.8s et %4.2s", "tuuu", "12345", "hu");
	//printf("\n");
	//printf("%1.4s et %-6.8s et %4.2s", "tuuu", "12345", "hu");
	//printf("\n");
	//ft_printf("%%|%%%%|%%%%%%|%%abc%%def%%ghi%%");
	//printf("\n");
	//printf("%%|%%%%|%%%%%%|%%abc%%def%%ghi%%");
	//printf("\n");
	//ft_printf("%Lf", 1.0e309L);
	//printf("\n");
	//printf("%Lf", 1.0e309L);
	//printf("\n");
	//ft_printf("% ");
	//printf("\n");
	//printf("% ");
	//printf("\n");

	/*
	**	FFT_SPRINT & FT_SNPRINTF + FT_DPRINTF & FT_DNPRINTF + FT_VPRINTF
	*/	

	//ft_sprintf(&s, "%rs", "\t");
	//ft_putstr(s);
	//printf("\n");
	//_vfunction("%s", str);
	//fd = open("./testfile" ,O_CREAT | O_RDWR);
	//ft_dnprintf(fd, 4, "%s", "testtest");	

	//ft_printf("%-01.5u", 1U);
	//printf("\n");
	//printf("%-01.5u", 1U);
	//printf("\n");
	//ft_printf("%.u|%-.u|%0.u", UINT_MAX, UINT_MAX, UINT_MAX);
	//printf("\n");
	//printf("%.u|%-.u|%0.u", UINT_MAX, UINT_MAX, UINT_MAX);
	//printf("\n");
	//ft_printf("%.5u|%-.5u|%0.5u", UINT_MAX, UINT_MAX, UINT_MAX);
	//printf("\n");
	//printf("%.5u|%-.5u|%0.5u", UINT_MAX, UINT_MAX, UINT_MAX);
	//printf("\n");
	//ft_printf("%23u|%-23u|%023u", 0U, 0U, 0U);
	//printf("\n");
	//printf("%23u|%-23u|%023u", 0U, 0U, 0U);
	//printf("\n");
	//ft_printf(""%-#23.5hho|%-023.5hho|%#023.5hho|%-#023.5hho", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX");
	//printf("\n");
	//printf("%-#23.5hho|%-023.5hho|%#023.5hho|%-#023.5hho", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	//printf("\n");
	//ft_printf("%s", "wi32x-3vx++===98234z1esfatr");
	//printf("\n");
	//printf("%s", "wi32x-3vx++===98234z1esfatr");
	//printf("\n");
	//ft_printf("%.f|%-.f|%+.f|% .f|%#.f|%0.f", 0., 0., 0., 0., 0., 0.);
	//printf("\n");
	//printf("%.f|%-.f|%+.f|% .f|%#.f|%0.f", 0., 0., 0., 0., 0., 0.);
	//printf("\n");
	ft_printf("%g|%-g|%+g|% g|%#g|%0g", 0., 0., 0., 0., 0., 0.);
	printf("\n");
	printf("%g|%-g|%+g|% g|%#g|%0g", 0., 0., 0., 0., 0., 0.);
	printf("\n");
	return (0);
}
