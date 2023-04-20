# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 13:59:50 by phudyka           #+#    #+#              #
#    Updated: 2023/04/20 14:26:03 by phudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		=	src/main/main.c src/main/prompt.c 	\
				src/parsing/parse.c 				\

INCLUDE		=	include/main.h \

OBJS		=	$(SRCS:%.c=%.o)

# /*------------LIBFT----------------*/
LIBFT		=	libft/libft.a

# /*------------COMPIL---------------*/
CFLAGS		=	-Wall -Werror -Wextra -lreadline
CC			=	gcc

RM			=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS) $(GNL_OBJS)
			make -C libft	
			make clean -C libft
			$(CC) $(SRCS) $(LIBFT) $(GNL_OBJS) $(CFLAGS) -o $(NAME)

%o:			%.c $(INCLUDE)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)
			$(RM) $(GNL_OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) *.out
			make fclean -C libft/

re:			fclean all

.PHONY:		all clean fclean re


