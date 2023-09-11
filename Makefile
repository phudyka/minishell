# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 13:59:50 by phudyka           #+#    #+#              #
#    Updated: 2023/09/11 15:36:28 by phudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		=	src/main/main.c src/main/prompt.c src/main/builtin.c	\
				src/main/exec.c src/main/env.c src/main/exit.c 			\
				src/main/signals.c	src/main/list.c src/main/pipes.c	\
				src/main/utils_export.c src/main/utils_prompt.c 		\
				src/main/utils_redir.c 									\
				src/main/print.c src/main/utils.c		 				\
				src/main/redir.c src/parser/lex.c src/parser/redir.c	\
				src/parser/parse.c	src/main/exit_status.c              \
				src/parser/parse_utils.c src/parser/token.c	 			\
				src/parser/split.c src/parser/split_utils.c 			\
				src/expander/utils_dollar.c src/expander/expand.c 		\
				src/expander/dollar.c src/error/error.c 				\
				src/main/utils_pipes.c src/main/utils_pipes2.c          \

INCLUDE		=	include/main.h include/parse.h include/expander.h 		\

OBJS		=	$(SRCS:%.c=%.o)	

LIBFT		=	libft/libft.a

CC			=	gcc -g
ifeq ($(shell uname), Darwin)
CFLAGS		=	-g -Wall -Werror -Wextra -I /Users/$(USER)/.brew/opt/readline/include
LDFLAGS		=	-L /Users/$(USER)/.brew/opt/readline/lib -lreadline
else
CFLAGS		=	-Wall -Werror -Wextra
LDFLAGS		=	-lreadline
endif

RM			=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			make -C libft	
			make clean -C libft
			$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(LDFLAGS) -o $(NAME)

%.o:		%.c $(INCLUDE)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) *.out
			make fclean -C libft/

re:			fclean all

.PHONY:		all clean fclean re
