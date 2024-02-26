#!/bin/sh
cc -g3 -Wall -Werror -Wextra -fsanitize=address -c show_one_env.c  -I../../inc/ 
#cc -fsanitize=address -o show_one_env  show_one_env.o -L../../lib/ -l:libargpar.a -l:libft.a -l:libftprintf.a 
cc -fsanitize=address -o show_one_env  show_one_env.o -L../../lib/ -largpar -lft -lftprintf 
