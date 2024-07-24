# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 09:46:26 by acaffard          #+#    #+#              #
#    Updated: 2024/07/01 16:56:45 by acaffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM=rm -rf

CYAN='\033[1;36m'
BLUE='\033[1;34m'
PURPLE='\033[6;35m'
GREEN='\033[6;32m'
WHITE='\033[0;m'

INCLUDES_PATH = includes
INCLUDES =  $(INCLUDES_PATH)/builtins.h $(INCLUDES_PATH)/errors.h $(INCLUDES_PATH)/minishell.h $(INCLUDES_PATH)/parsing.h \
			$(INCLUDES_PATH)/s_arglist.h $(INCLUDES_PATH)/s_cmdlist.h $(INCLUDES_PATH)/s_redlist.h $(INCLUDES_PATH)/utils.h

LIBFT_DIR = includes/LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

BUILTINS_DIR =	$(SRC_PATH)/builtins
BUILTINS =	$(BUILTINS_DIR)/ft_add_new_node.c $(BUILTINS_DIR)/ft_append_node.c $(BUILTINS_DIR)/ft_env_var_len.c \
			$(BUILTINS_DIR)/ft_export.c $(BUILTINS_DIR)/ft_get_env_node.c $(BUILTINS_DIR)/ft_print_sorted_env.c \
			$(BUILTINS_DIR)/ft_cd.c $(BUILTINS_DIR)/ft_exit.c $(BUILTINS_DIR)/ft_env.c $(BUILTINS_DIR)/ft_pwd.c $(BUILTINS_DIR)/ft_unset.c \
			$(BUILTINS_DIR)/update_env_var.c $(BUILTINS_DIR)/ft_echo.c

ARGLIST_DIR = $(SRC_PATH)/t_arglist
ARGLIST =	$(ARGLIST_DIR)/ft_argclear.c $(ARGLIST_DIR)/ft_argdelone.c $(ARGLIST_DIR)/ft_arglast.c $(ARGLIST_DIR)/ft_argnew.c \
			$(ARGLIST_DIR)/ft_argpop_two.c $(ARGLIST_DIR)/ft_argpush.c

REDLIST_DIR = $(SRC_PATH)/t_redlist
REDLIST = 	$(REDLIST_DIR)/ft_red_delone.c $(REDLIST_DIR)/ft_redclear.c $(REDLIST_DIR)/ft_redget_type.c $(REDLIST_DIR)/ft_redlast.c \
			$(REDLIST_DIR)/ft_rednew.c $(REDLIST_DIR)/ft_redpush.c

CMDLIST_DIR = $(SRC_PATH)/t_cmdlist
CMDLIST =	$(CMDLIST_DIR)/ft_cmd_delone.c $(CMDLIST_DIR)/ft_cmd_size.c $(CMDLIST_DIR)/ft_cmdclear.c $(CMDLIST_DIR)/ft_cmdlast.c \
			$(CMDLIST_DIR)/ft_cmdnew.c $(CMDLIST_DIR)/ft_cmdpush.c

UTILS_DIR = $(SRC_PATH)/utils
UTILS = $(UTILS_DIR)/print_error.c $(UTILS_DIR)/skip_quotes.c $(UTILS_DIR)/ft_prompt.c $(UTILS_DIR)/is_space.c \
		$(UTILS_DIR)/list_to_array.c $(UTILS_DIR)/skip_spaces.c $(UTILS_DIR)/arg_tabs.c $(UTILS_DIR)/main_utils.c \
		$(UTILS_DIR)/delete_cote_utils.c $(UTILS_DIR)/pipe_utils.c

PARSING_DIR = $(SRC_PATH)/parsing
PARSING = $(PARSING_DIR)/fill_command.c $(PARSING_DIR)/fill_redlist.c $(PARSING_DIR)/ft_fill_cmdline.c $(PARSING_DIR)/lexer.c

EXPAND_DIR = $(SRC_PATH)/expand
EXPAND = $(EXPAND_DIR)/delete_cote.c $(EXPAND_DIR)/expand_get_value.c $(EXPAND_DIR)/main_expand.c

EXEC_DIR = $(SRC_PATH)/execution
EXEC =	$(EXEC_DIR)/child_and_parent.c $(EXEC_DIR)/execute_multi.c $(EXEC_DIR)/execute_single.c $(EXEC_DIR)/heredoc.c \
		$(EXEC_DIR)/main_pipe.c $(EXEC_DIR)/redirect_pipe.c $(EXEC_DIR)/signaux.c $(SRC_PATH)/redirection/main_redirection.c\
		$(SRC_PATH)/redirection/all_heredoc.c $(SRC_PATH)/redirection/init_heredoc.c $(EXEC_DIR)/heredoc_utils.c

SRC_PATH = src
SRCS = 	$(ARGLIST) \
		$(REDLIST) \
		$(CMDLIST) \
		$(UTILS) \
		$(BUILTINS) \
		$(PARSING) \
		$(EXPAND) \
		$(EXEC) \
		$(SRC_PATH)/main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(LIBFT) $(INCLUDES) $(OBJS)

	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@clear
	@if [ $$? -eq 0 ]; then \
		echo ${GREEN}">-Compilation successful-<"${WHITE}; \
	fi

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@echo ${PURPLE} ">- COMPILING LIBFT ...... -<"${WHITE}
	@make --no-print --directory $(LIBFT_DIR)
	@clear
	@echo ${PURPLE} ">- COMPILING MINISHELL...... -<"${WHITE}

clean :
	@make clean --no-print --directory $(LIBFT_DIR)
	@clear
	@$(RM) $(OBJS)
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@clear
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}
	@echo ${CYAN}">-------Name clean-------<\n"${WHITE}

re: fclean all
	@clear
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}
	@echo ${CYAN}">-------Name clean-------<\n"${WHITE}
	@echo ${GREEN}">-Compilation successful-<"${WHITE}

bonus : all

.PHONY: all clean fclean re bonus
