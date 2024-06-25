# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 09:46:26 by acaffard          #+#    #+#              #
#    Updated: 2024/06/25 14:00:33 by acaffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM=rm -rf

CYAN='\033[1;36m'
BLUE='\033[1;34m'
PURPLE='\033[6;35m'
GREEN='\033[6;32m'
WHITE='\033[0;m'

INCLUDES_PATH = includes
INCLUDES =  $(INCLUDES_PATH)/s_int_list.h

LIBFT_DIR = includes/LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

INT_LIST_DIR = $(SRC_PATH)/t_int_list
INT_LIST =	$(INT_LIST_DIR)/ft_int_lstnew.c $(INT_LIST_DIR)/ft_int_lstlast.c $(INT_LIST_DIR)/ft_int_lstget_index.c \
			$(INT_LIST_DIR)/ft_int_lstsize.c $(INT_LIST_DIR)/ft_int_lstpush.c $(INT_LIST_DIR)/ft_int_lstpop_index.c \
			$(INT_LIST_DIR)/ft_int_lstclear.c

BUILTINS_DIR =	$(SRC_PATH)/builtins
BUILTINS =	$(BUILTINS_DIR)/ft_add_new_node.c $(BUILTINS_DIR)/ft_append_node.c $(BUILTINS_DIR)/ft_env_var_len.c \
			$(BUILTINS_DIR)/ft_export.c $(BUILTINS_DIR)/ft_get_env_node.c $(BUILTINS_DIR)/ft_print_sorted_env.c \
			$(BUILTINS_DIR)/update_env_var.c $(BUILTINS_DIR)/ft_cd.c $(BUILTINS_DIR)/ft_env.c $(BUILTINS_DIR)/ft_pwd.c \
			$(BUILTINS_DIR)/ft_unset.c

SRC_PATH = src
SRCS = 	$(INT_LIST) \
		$(BUILTINS) \
		$(SRC_PATH)/main.c $(SRC_PATH)/print_error.c

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
