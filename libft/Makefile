# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 11:36:19 by phudyka           #+#    #+#              #
#    Updated: 2023/04/27 14:03:14 by phudyka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRCS		=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c	\
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c				\
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c			\
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c			\
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c				\
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c			\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c			\
			ft_strcmp.c ft_strndup.c 												\

B_SRCS		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c 			\
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c 				\
			ft_lstmap.c

CC      = gcc

HEADER	= libft.h

CFLAGS  = -Wall -Werror -Wextra

OBJS    = $(SRCS:.c=.o)

B_OBJS	= $(B_SRCS:.c=.o)

RM      = rm -f

AR      = ar -rc

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean :
		$(RM) $(OBJS) $(B_OBJS)

fclean : clean
		$(RM) $(NAME)

bonus :		$(B_OBJS)
			$(AR) $(NAME) $(B_OBJS)

re : fclean all

.PHONY: all bonus clean fclean re
