# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishaimou <ishaimou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/05 19:04:43 by ishaimou          #+#    #+#              #
#    Updated: 2019/03/05 20:32:47 by obelouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = libft/libft.a

LIBFT_SRC_DIR = libft/*.c

LIBFT_OBJ_DIR = *.o

LIBFT_H = libft/libft.h

LIB_FT_PRINTF_SRC_DIR = src/*.c

LIB_FT_PRINTF_OBJ_DIR = *.o

LIB_FT_PRINTF_H = include/ft_printf.h

LIB = -L./libft/ -lft

FLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

$(LIBFT): $(LIBFT_H)
		  @cc -c $(FLAG) $(LIBFT_SRC_DIR)
		  @ar rc $(LIBFT) $(LIBFT_OBJ_DIR)
		  @ranlib $(LIBFT)

$(NAME): $(LIB_FT_PRINTF_H)
		 @cc -c $(FLAG) -I include/ -I libft/ $(LIB_FT_PRINTF_SRC_DIR)
		 @ar rc $(NAME) $(LIB_FT_PRINTF_OBJ_DIR)
		 @ranlib $(NAME)

clean:
		@/bin/rm -f $(LIB_FT_PRINTF_OBJ_DIR) $(LIBFT_OBJ_DIR)

fclean:
		@/bin/rm -f $(NAME) $(LIBFT)

re:		fclean all
