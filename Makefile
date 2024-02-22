NAME = minishell
CC = cc
CFLAGS= -Wall -Wextra -Werror -g

SRCS = test.c split_modif.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = includes/LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

PARSING_DIR = includes/parsing
PARSING = $(PARSING_DIR)/parsing_minishell.a

RM=rm -rf

CYAN='\033[1;36m'
BLUE='\033[1;34m'
GREEN='\033[6;32m'
WHITE='\033[0;m'

all : $(NAME)

$(NAME) : $(LIBFT) $(PARSING) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(PARSING) -lreadline
	@clear
	@if [ $$? -eq 0 ]; then \
		echo ${GREEN}">-Compilation successful-<"${WHITE}; \
	fi

%.o : %.c includes/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@make --directory $(LIBFT_DIR)

$(PARSING) :
	@make --directory $(PARSING_DIR)

clean :
	@make clean --directory $(LIBFT_DIR)
	@make clean --directory $(PARSING_DIR)
	@clear
	$(RM) $(OBJS)
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}

fclean : clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(PARSING)
	@clear
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}
	@echo ${CYAN}">-------Name clean-------<\n"${WHITE}

re: fclean all
	@clear
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}
	@echo ${CYAN}">-------Name clean-------<\n"${WHITE}
	@echo ${GREEN}">-Compilation successful-<"${WHITE}

.PHONY: all clean fclean re bonus
