# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 13:59:50 by phudyka           #+#    #+#              #
#    Updated: 2023/05/0 by phudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		=	src/main/main.c src/main/prompt.c src/main/builtin.c	\
				src/main/signals.c	src/main/free.c 					\
				src/parser/parse.c src/parser/quotes.c					\
				src/parser/parse_utils.c src/parser/pipes.c 			\
				
INCLUDE		=	include/main.h include/parse.h

OBJS		=	$(SRCS:%.c=%.o)

LIBFT		=	libft/libft.a

CC			=	gcc
ifeq ($(shell uname), Darwin)
CFLAGS		=	-g -Wall -Werror -Wextra -I /Users/$(USER)/.brew/opt/readline/include
LDFLAGS		=	-L /Users/$(USER)/.brew/opt/readline/lib -lreadline
else
CFLAGS		=	-g -Wall -Werror -Wextra
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
