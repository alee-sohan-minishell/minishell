# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/07 07:23:33 by alee              #+#    #+#              #
#    Updated: 2022/05/22 19:54:10 by alee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = minishell

FILE = main
LIBFT = $(addprefix libft/, libft.a)
#LIBFT_FILE = ft_isalnum ft_isprint ft_memcmp ft_putchar_fd ft_split \
			ft_strlcat ft_strncmp ft_substr ft_atoi ft_isalpha \
			ft_itoa ft_memcpy ft_putendl_fd ft_strchr ft_strlcpy \
			ft_strnstr ft_tolower ft_bzero ft_isascii ft_memccpy \
			ft_memmove ft_putnbr_fd ft_strdup ft_strlen ft_strrchr \
			ft_toupper ft_calloc ft_isdigit ft_memchr ft_memset \
			ft_putstr_fd ft_strjoin ft_strmapi ft_strtrim ft_strcmp \
			ft_lstadd_back ft_lstadd_front ft_lstclear \
			ft_lstdelone ft_lstiter ft_lstlast \
			ft_lstmap ft_lstnew ft_lstsize

LOGO_FILE = logo
SHELL_FILE = shell
INIT_FILE = shell_init
READ_LINE_FILE = shell_readline
UTILS_FILE = utils_01 utils_02
BUILT_IN_FILE = ft_pwd ft_cd ft_echo ft_exit
ENV_FILE = env_list env_utils_01 env_list_interface


READLINE_ROOT = $(shell brew --prefix readline)
READLINE_INCLUDE = $(READLINE_ROOT)/include
READLINE_LIB = $(READLINE_ROOT)/lib


SRC = $(addsuffix .c,$(FILE)) \
	$(addprefix logo/,$(addsuffix .c,$(LOGO_FILE))) \
	$(addprefix shell/,$(addsuffix .c,$(SHELL_FILE))) \
	$(addprefix init/,$(addsuffix .c,$(INIT_FILE)))	\
	$(addprefix read_line/,$(addsuffix .c,$(READ_LINE_FILE)))	\
	$(addprefix built_in/,$(addsuffix .c,$(BUILT_IN_FILE)))	\
	$(addprefix env/,$(addsuffix .c,$(ENV_FILE))) \
	$(addprefix utils/,$(addsuffix .c,$(UTILS_FILE))) \

OBJ = $(SRC:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -L$(READLINE_LIB) -lreadline -lhistory $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -I$(READLINE_INCLUDE) -c $(CFLAGS) -o $@ $<

$(LIBFT):
	@echo "make libft"
	@make -C libft/

.PHONY: clean
clean:
	$(RM) $(OBJ)
	@make -C libft/ clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	@make -C libft/ fclean

.PHONY: re
re:
	make fclean
	make all
