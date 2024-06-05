# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 14:08:21 by acaffard          #+#    #+#              #
#    Updated: 2024/06/04 14:21:04 by acaffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = builtins_minishell.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = cd.c echo.c env.c exit.c export.c pwd.c unset.c export_utils.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ../LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

PARSING_DIR = ../parsing
PARSING = $(PARSING_DIR)/parsing_minishell.a

RM = rm -rf

all : $(NAME)

$(NAME): $(LIBFT) $(PARSING) $(OBJS)
	@ar rcs $(NAME) $(OBJS) $(LIBFT) $(PARSING)

%.o : %.c builtins_minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@make --directory $(LIBFT_DIR)

$(PARSING) :
	@make --directory $(PARSING_DIR)

clean :
	$(RM) $(OBJS)
	@make clean --directory $(LIBFT_DIR)
	@make clean --directory $(PARSING_DIR)

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@$(RM) $(PARSING)

re : fclean all

.PHONY : all, re, clean, fclean
