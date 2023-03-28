# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 12:01:27 by phudyka           #+#    #+#              #
#    Updated: 2023/03/28 16:01:39 by phudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
SRC  =  source/main.c source/lexer.c 	\
		source/parser.c source/exec.c 	\
		source/utils.c 					\
		 
OBJ = $(patsubst %.c,%.o,$(SRC))
INCLUDES = minishell.h

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