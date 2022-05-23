# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/13 21:20:01 by alee              #+#    #+#              #
#    Updated: 2022/05/23 03:00:48 by alee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
NAME = libft.a
HEADER = libft.h
RM = rm -f

SOURCES = ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
			ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
			ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
			ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memccpy.c \
			ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_strrchr.c \
			ft_toupper.c ft_calloc.c ft_isdigit.c ft_memchr.c ft_memset.c \
			ft_putstr_fd.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_strcmp.c
			
OBJECTS = $(SOURCES:.c=.o)

SOURCES_B = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
				ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
				ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJECTS_B = $(SOURCES_B:.c=.o)

ifdef BONUS
	OBJECTS_TOTAL = $(OBJECTS) $(OBJECTS_B)
else
	OBJECTS_TOTAL = $(OBJECTS)
endif

all : $(NAME)

.PHONY : clean
clean :
	$(RM) $(OBJECTS) $(OBJECTS_B)

.PHONY : fclean
fclean : clean
	$(RM) $(NAME)

.PHONY : re
re : fclean all

.PHONY : bonus
bonus :
	@make BONUS=1 all

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJECTS_TOTAL)
	$(AR) $@ $^
