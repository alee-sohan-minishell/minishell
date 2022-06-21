# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/07 07:23:33 by alee              #+#    #+#              #
#    Updated: 2022/06/21 14:47:25 by alee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -fsanitize=address -g
CC = cc
CFLAGS = -Wall -Wextra -Werror #-MD
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
SHELL_FILE =
INIT_FILE = shell_init shell_utils_01
READ_LINE_FILE = shell_readline
UTILS_FILE = fd_utils_01 error_msg_utils_01 state_machine_utils_01 command_utils_01 \
			string_utils_01 integer_utils_01 pipe_utils_01
BUILT_IN_FILE = ft_pwd ft_cd ft_echo ft_exit ft_env ft_unset ft_export ft_export_utils
ENV_FILE = env_list env_utils_01 env_list_interface_01 env_list_interface_02
SIGNAL_FILE = signal
NON_BUILT_IN_FILE = non_built_in
SHELL_PARSE_FILE = shell_parse
EXCUTE_FILE = shell_excute
REDIRECTION_FILE = redirection
HEREDOC_FILE = heredoc

READLINE_ROOT = $(shell brew --prefix readline)
READLINE_INCLUDE = $(READLINE_ROOT)/include
READLINE_LIB = $(READLINE_ROOT)/lib

CPPFLAGS += -I$(READLINE_INCLUDE)
LIBADD += -L$(READLINE_LIB) -lreadline -lhistory


SRC = $(addsuffix .c,$(FILE)) \
	$(addprefix logo/,$(addsuffix .c,$(LOGO_FILE))) \
	$(addprefix shell/,$(addsuffix .c,$(SHELL_FILE))) \
	$(addprefix init/,$(addsuffix .c,$(INIT_FILE)))	\
	$(addprefix read_line/,$(addsuffix .c,$(READ_LINE_FILE)))	\
	$(addprefix built_in/,$(addsuffix .c,$(BUILT_IN_FILE)))	\
	$(addprefix env/,$(addsuffix .c,$(ENV_FILE))) \
	$(addprefix utils/,$(addsuffix .c,$(UTILS_FILE))) \
	$(addprefix signal/,$(addsuffix .c,$(SIGNAL_FILE))) \
	$(addprefix non_built_in/,$(addsuffix .c,$(NON_BUILT_IN_FILE))) \
	$(addprefix parse/,$(addsuffix .c,$(SHELL_PARSE_FILE))) \
	$(addprefix excute/,$(addsuffix .c,$(EXCUTE_FILE))) \
	$(addprefix redirection/,$(addsuffix .c,$(REDIRECTION_FILE))) \
	$(addprefix heredoc/,$(addsuffix .c,$(HEREDOC_FILE))) \




OBJ = $(SRC:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LIBADD) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	@echo "make libft"
	@make -C libft/

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ:.o=.d)
	@make -C libft/ clean

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	@make -C libft/ fclean

.PHONY: re
re:
	make fclean
	make all

-include $(OBJ:.o=.d)
