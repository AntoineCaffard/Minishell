CC : cc
CFLAGS : -Wall -Wextra -Werror -g
SRCS : parsing_cd.c parsing_echo.c parsing_env.c parsing_exit.c parsing_export.c parsing_pwd.c parsing_unset.c
OBJS : $(SRCS:.c=.o)
NAME : parsing_minishell.a

RM : rm -rf

CYAN='\033[1;36m'
BLUE='\033[1;34m'
GREEN='\033[6;32m'
WHITE='\033[0;m'

all : $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o : %.c parsing_minishell.h
	$(CC) $(CFLAGS) -c $< -o $@
