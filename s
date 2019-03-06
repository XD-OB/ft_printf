#!/bin/bash
gcc main.c -L./libft -lft -L./ -lftprintf -I include/ -I libft/ -o ft_printf
