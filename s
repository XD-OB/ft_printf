#!/bin/bash
gcc -L./libft -lft -L./ -lftprintf -I libft -I include main.c -o ft_printf
