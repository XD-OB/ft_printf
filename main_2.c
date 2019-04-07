#include "./ft_printf.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(void)
{
	char		*str;

	str = "This is a test text";
	
	//ft_printf("TEST1---%06.2x", 5427);
	//printf("\n");
	//printf("ORIG ---%06.2x", 5427);
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
	//ft_printf("TEST22---@moulitest: %5.d %5.0d", 0, 0);
	//printf("\n");
	//printf("ORIG  ---@moulitest: %5.d %5.0d", 0, 0);
	//printf("\n");
	//ft_printf("%%");
	//printf("\n");
	//printf("%%");
	//printf("\n");
	//ft_printf("%5.2x", 5427);
	//printf("\n");
	//printf("%5.2x", 5427);
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
	//ft_printf("TEST : u%4.2ss %-1.s\n %---5.3s", "coco", NULL, "yooo");
	//printf("\n");
	//printf("TEST : u%4.2ss %-1.s\n %---5.3s", "coco", NULL, "yooo");
	//printf("\n");
	//ft_printf("%1.4s et %-6.8s et %4.2s", "tuuu", "12345", "hu");
	//printf("\n");
	//printf("%1.4s et %-6.8s et %4.2s", "tuuu", "12345", "hu");
	//printf("\n");
	ft_printf("%%|%%%%|%%%%%%|%%abc%%def%%ghi%%");
	printf("\n");
	printf("%%|%%%%|%%%%%%|%%abc%%def%%ghi%%");
	printf("\n");
	return (0);
}
