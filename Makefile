NAME = libftprintf.a

LIBFT  = ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove ft_memchr\
		 ft_memcmp ft_memalloc ft_memdel ft_strnew ft_strdel ft_strclr\
		 ft_striter ft_striteri ft_strmap ft_strmapi ft_strequ ft_strnequ\
		 ft_strsub ft_strjoin ft_strtrim ft_strsplit ft_itoa ft_itoa_base\
		 ft_utoa ft_utoa_base ft_putchar ft_putstr ft_putendl ft_putnbr\
		 ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_strlen\
		 ft_strcpy ft_strncpy ft_strcat ft_strncat ft_strlcat ft_strstr\
		 ft_strnstr ft_strcmp ft_strncmp ft_strchr ft_strrchr ft_strpbrk\
		 ft_strdup ft_strndup ft_atoi ft_isalpha ft_isdigit ft_isalnum\
		 ft_isascii ft_isprint ft_toupper ft_tolower ft_lstnew ft_lstdelone\
		 ft_lstdel ft_lstadd ft_lstiter ft_lstmap ft_sqrt ft_prime\
		 ft_strlowcase ft_strupcase ft_swap ft_strrev ft_isblank ft_isxdigit\
		 ft_strnjoin ft_atoi_base ft_strswap ft_strsum ft_str_pushback ft_ulltoa ft_lltoa ft_strmult ft_strcnew ft_ltoa\

LIBFT_OBJ = $(addprefix libft/, $(addsuffix .o, $(LIBFT)))

LIB_FT_PRINTF = ft_printf check parse tools tools2 date noprint flags flags2 engine\
			convers_cs precalc delete_me put_chr convers_efgh convers_ee

LIB_FT_PRINTF_SRC = $(addprefix src/, $(addsuffix .c, $(LIB_FT_PRINTF)))

LIB_FT_PRINTF_OBJ = $(addsuffix .o, $(LIB_FT_PRINTF))

LIBFT_H_DIR = libft/

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
		@make -C libft
		@gcc -c  $(FLAGS) -I ./ -I $(LIBFT_H_DIR) $(LIB_FT_PRINTF_SRC)
		@ar rc $(NAME) $(LIBFT_OBJ) $(LIB_FT_PRINTF_OBJ)
		@ranlib	$(NAME)

clean :
		@make clean -C libft
		@/bin/rm -rf $(LIB_FT_PRINTF_OBJ)

fclean : clean
		@make fclean -C libft
		@/bin/rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
