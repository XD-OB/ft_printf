#include "ft_printf.h"

int				main(void)
{
	char	*str;

	str = "this is a test string";

	ft_printf("");
	ft_printf("\n");
	ft_printf("%%\n");
	ft_printf("%d\n", 42);
	ft_printf("%d%d\n", 42, 41);
	ft_printf("%d%d%d\n", 42, 43, 44);
	ft_printf("%ld\n", 2147483647);
	ft_printf("%lld\n", 9223372036854775807);
	ft_printf("%x\n", 505);
	ft_printf("%X\n", 505);
	ft_printf("%20.15d\n", 54321);
	ft_printf("%-10d\n", 3);
	ft_printf("% d\n", 3);
	ft_printf("%+d\n", 3);
	ft_printf("%010d\n", 1);
	ft_printf("%hhd\n", 0);
	ft_printf("%i\n", 1337);
	ft_printf("%-+.i|%- .i|%-0.i|%+ .i|%+0.i|% 0.i|%-+ 0.i\n", 0, 0, 0, 0, 0, 0, 0);
	ft_printf("%23i|%-23i|%+23i|% 23i|%023i\n", INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN);
	ft_printf("%1.5i|%-1.5i|%+1.5i|% 1.5i|%01.5i\n", INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX);
	ft_printf("%hhi|%-hhi|%+hhi|% hhi|%0hhi\n", LLONG_MAX, LLONG_MAX, LLONG_MAX, LLONG_MAX, LLONG_MAX);
	ft_printf("%\n");
	ft_printf("%U\n", 4294967295);
	ft_printf("%u\n", 4294967295);
	ft_printf("%u|%-u|%0u\n", 0U, 0U, 0U);
	ft_printf("%23u|%-23u|%023u\n", UINT_MAX, UINT_MAX, UINT_MAX);
	ft_printf("%23.5hu|%-23.5hu|%023.5hu", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	ft_printf("%llu|%-llu|%0llu", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	ft_printf("%o\n", 40);
	ft_printf("%-#23.5o|%-023.5o|%#023.5o|%-#023.5o\n", 0U, 0U, 0U, 0U);
	ft_printf("%1o|%-1o|%#o|%01o\n", UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX);
	ft_printf("%%#08x\n", 42);
	ft_printf("%x\n", 1000);
	ft_printf("%23lx|%-23lx|%#lx|%023lx\n", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	ft_printf("%-#1.5hx|%-01.5hx|%#01.5hx|%-#01.5hx\n", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	ft_printf("%-#.hhx|%-0.hhx|%#0.hhx|%-#0.hhx", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	ft_printf("%#X\n", 1000);
	ft_printf("%23lX|%-23lX|%#lX|%023lX\n", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	ft_printf("%-#1.5hX|%-01.5hX|%#01.5hX|%-#01.5hX\n", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	ft_printf("%-#.hhX|%-0.hhX|%#0.hhX|%-#0.hhX\n", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
	printf("%-#.hhX|%-0.hhX|%#0.hhX|%-#0.hhX\n", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);

	ft_printf("%s\n", NULL);
	ft_printf("%s%s\n", "test", "test");
	ft_printf("%s%s%s\n", "test", "test", "test");
	ft_printf("%c|%-c|%12c|%-12c\n", 0, 0, 0, 0);
	ft_printf("%20c|%020c|%-020c\n", 65, 65, 65);
	ft_printf("%c|%-c|%12c|%-12.5c\n", 1345, 1345, 1345, 1345);
	ft_printf("%p\n", NULL);
	ft_printf("%p\n", "test");
	ft_printf("%p|%5p|%30p|%-30p\n", str, str, str, str);
	ft_printf("%p|%5p|%30p|%-30p\n", &str, &str, &str, &str);
	ft_printf("%%|%%%%|%%%%%%|%%abc%%def%%ghi%%\n");
	ft_printf("WwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqpWwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqpWwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqpWwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqpWwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqpWwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqpWwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqpWwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqpWwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqpWwyAlxbZGYIJZGzkjomuMGJgEuAZPbUAUimRUBeAAyoSGmhJCGmBOguEdCViaCsqohhsuRGLkoFQNmTZEZQFLEwvHAEctloDFOpLZGQyDDexpPllnNXympcKOxDyygGcWpdzqp\n");
	//ft_printf("%f\n", 0.00222);
	//ft_printf("%lf\n", 3.14);
	//ft_printf("%Lf\n", 0.014e-15L);
	
	//while (1);
	return (0);
}
