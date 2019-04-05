# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/06 14:55:40 by obelouch          #+#    #+#              #
#    Updated: 2019/04/06 00:29:57 by obelouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = *.c

HEAD = libft.h

OUTO = *.o

OPT = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(HEAD)
	@gcc -c $(SRCS) $(OPT)
	@ar rc $(NAME) $(OUTO)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OUTO)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
