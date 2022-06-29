# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/07 07:23:33 by alee              #+#    #+#              #
#    Updated: 2022/06/28 22:10:08 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -MD -g $(if $(SANITIZER),-fsanitize=$(SANITIZER))
RM = rm -f

NAME = minishell

FILE = main print
LIBFT = $(addprefix libft/, libft.a)

LOGO_FILE = logo
INIT_FILE = shell_init shell_utils_01 shell_parse_init
READ_LINE_FILE = shell_readline
UTILS_FILE = fd_utils_01 error_msg_utils_01 error_msg_utils_02 state_machine_utils_01 command_utils_01 \
			string_utils_01 integer_utils_01
BUILT_IN_FILE = ft_pwd ft_cd ft_echo ft_exit ft_env ft_unset ft_export ft_export_utils
ENV_FILE = env_list env_utils_01 env_list_interface_01 env_list_interface_02
SIGNAL_FILE = signal_with_no_foreground_process signal_with_foreground_process
NON_BUILT_IN_FILE = ft_non_built_in direct_execute search_execute
EXECUTE_FILE = shell_execute_command_name shell_execute_tree shell_execute_tree_utils pipe_utils tree_traverse_execute
REDIRECTION_FILE = redirection
HEREDOC_FILE = heredoc
SHELL_PARSE_FILE = shell_parse_check_tree shell_parse_node_list \
			shell_parse_state shell_parse_state1 shell_parse_state2 \
			shell_parse_state3 shell_parse_state4 shell_parse_state5 \
			shell_parse_util_node_list shell_parse_util_state \
			shell_parse_util_tree shell_parse shell_parse_util_tree_push \
			shell_parse_util_tree2 shell_parse_util_state2
TREE_HEREDOC_FILE = shell_tree shell_heredoc

READLINE_ROOT = $(shell brew --prefix readline)
READLINE_INCLUDE = $(READLINE_ROOT)/include
READLINE_LIB = $(READLINE_ROOT)/lib

CPPFLAGS += -I$(READLINE_INCLUDE)
LIBADD += -L$(READLINE_LIB) -lreadline -lhistory


SRC = $(addsuffix .c,$(FILE)) \
	$(addprefix logo/,$(addsuffix .c,$(LOGO_FILE))) \
	$(addprefix init/,$(addsuffix .c,$(INIT_FILE)))	\
	$(addprefix read_line/,$(addsuffix .c,$(READ_LINE_FILE)))	\
	$(addprefix built_in/,$(addsuffix .c,$(BUILT_IN_FILE)))	\
	$(addprefix env/,$(addsuffix .c,$(ENV_FILE))) \
	$(addprefix utils/,$(addsuffix .c,$(UTILS_FILE))) \
	$(addprefix signal/,$(addsuffix .c,$(SIGNAL_FILE))) \
	$(addprefix non_built_in/,$(addsuffix .c,$(NON_BUILT_IN_FILE))) \
	$(addprefix execute/,$(addsuffix .c,$(EXECUTE_FILE))) \
	$(addprefix redirection/,$(addsuffix .c,$(REDIRECTION_FILE))) \
	$(addprefix parse/,$(addsuffix .c,$(SHELL_PARSE_FILE))) \
	$(addprefix tree_heredoc/,$(addsuffix .c,$(TREE_HEREDOC_FILE))) \
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
