# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 12:01:27 by phudyka           #+#    #+#              #
#    Updated: 2023/04/17 11:50:18 by phudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
SRC =	source/main.c source/lexer.c 	\mmit -m 
		source/parser.c source/exec.c 	\
		source/utils.c source/error.c 	\

INCLUDES =	include/main.h include/lexer.h 	\
			include/parser.h include/exec.h \
			include/utils.h include/error.h \

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.c,%.o,$(SRC)))

all : $(NAME)

$(NAME) : $(OBJ)
@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.c $(INCLUDES)
@mkdir -p $(OBJ_DIR)
@$(CC) $(CFLAGS) -c $< -o $@

clean :
rm -rf $(OBJ_DIR)

fclean : clean
rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re