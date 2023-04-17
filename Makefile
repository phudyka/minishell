# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 12:01:27 by phudyka           #+#    #+#              #
#    Updated: 2023/04/17 14:02:25 by phudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
SRC  =  source/main.c source/lexer.c 	\
		source/parser.c source/exec.c 	\
		source/utils.c 	source/error.c	\
		 
INCLUDES =	include/main.h include/lexer.h	\
			include/parser.h include/exec.h \
			include/utils.h include/error.h	\

OBJ = $(patsubst %.c,%.o,$(SRC))
all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(INCLUDES)
	gcc $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	
re : fclean all

.PHONY : all clean fclean re
