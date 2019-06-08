*       TEAM: (A7ssen printf)      obelouch : ishaimou
# FT_PRINTF

By now, you must be fed up alternating the ft_putstr and ft_putnbr functions when doing your printing. Are you not allowed to use printf? You can recode yours! It will be a chance for you to discover a feature of the C language – variadic functions – and to practice detailed management of the printing options. You will then be allowed to use your ft_printf in all your future projects.
The versatility of the printf function in C represents a great exercise in programming for us. This project is of moderate difficulty. It will enable you to discover variadic functions in C in a particularly relevant context as well as learn about a great example of a basic “dispatcher” in C via the use of an array of function’s pointers.
The key to a successful ft_printf is a well-structured and good extensible code. This is because as time goes by, you will be more and more tempted to continue to extend your ft_printf, making your life easier for your future projects. So take your time to code properly while keeping in mind that you will have to read again your code in a few weeks or a few months to extend its functionality according to your needs. It would be a shame not to being able to do it because your can’t read your own work.

* conversions	:			cspdiouxXf
* flags			:			#0- +
* format modifier:			h hh l ll L
* minimum field width
* precision

* ADDITIONAL BONUS:

ft_sprintf   the result will be affect to a string

ft_snprintf  the n first result will be affected to a string

ft_dprintf   the result will be writed in a file (or STDOUT) depend in the fd argument

ft_dnprintf  the first n result will be writed in a file (or STDOUT) depend in the fd argument

ft_vprintf	same as printf but it use a va_list (list of argument)

colors		%{color}	(RED, red, BLUE, blue ...)

%k			print date with a timestamp argument

%b(B)		print a number in binary form

'*'			wildcard for precision & width

$			choose argument

'			thousands separator

%H			print float or double in Hexadecimal

%(L)e(E)	float and double in xxe+-xx format

%(L)g(G)
