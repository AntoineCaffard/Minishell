NAME = Minishell
SRCS = test.c split_modif.c
OBJS=$(SRCS:.c=.o)
RM=rm -rf
CC= cc
CFLAGS= -Wall -Wextra -Werror -g

CYAN='\033[1;36m'
BLUE='\033[1;34m'
GREEN='\033[6;32m'
WHITE='\033[0;m'

all: $(NAME)

$(NAME) : $(OBJS)
	@make --directory libft
	@make --directory pipex
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a -lreadline
	@clear
	@if [ $$? -eq 0 ]; then \
		echo ${GREEN}">-Compilation successful-<"${WHITE}; \
	fi
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 
clean:
	@make clean --directory pipex
	@make clean --directory libft
	@clear
	@$(RM) $(OBJS)
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}
fclean: clean
	@make fclean --directory pipex
	@make fclean --directory libft
	@$(RM) $(NAME)
	@clear
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}
	@echo ${CYAN}">-------Name clean-------<\n"${WHITE}
re: fclean all
	@clear
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}
	@echo ${CYAN}">-------Name clean-------<\n"${WHITE}
	@echo ${GREEN}">-Compilation successful-<"${WHITE}

.PHONY: all clean fclean re
