NAME = parsing_minishell.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = parsing_cd.c parsing_echo.c parsing_env.c parsing_exit.c parsing_export.c parsing_pwd.c parsing_unset.c
OBJS = $(SRCS:.c=.o)


LIBFT_DIR = ../LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

RM = rm -rf

all : $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS) $(LIBFT)

%.o : %.c parsing_minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@make --directory $(LIBFT_DIR)

clean :
	$(RM) $(OBJS)
	@make clean --directory $(LIBFT_DIR)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re : fclean all

.PHONY : all, re, clean, fclean
