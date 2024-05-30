NAME = minishell
CC = cc
CFLAGS= -Wall -Wextra -Werror -g

SRCS = bin/display_error.c bin/minishell.c bin/creat_t_list_or_stringtab.c bin/execute_other_cmd.c \
	bin/pipe.c bin/redirection.c bin/parser.c bin/lists/s_argument.c bin/lists/s_command.c bin/lists/s_redirection.c \
	bin/utils.c bin/free_struct.c bin/signaux.c bin/expand.c bin/expand_utils.c bin/delete_quote.c bin/lexer.c \
	bin/creat_t_args_or_stringtab.c bin/quote_utils.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = includes/LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

PARSING_DIR = includes/parsing
PARSING = $(PARSING_DIR)/parsing_minishell.a

BUILTINS_DIR = includes/builtins
BUILTINS = $(BUILTINS_DIR)/builtins_minishell.a

RM=rm -rf

CYAN='\033[1;36m'
BLUE='\033[1;34m'
GREEN='\033[6;32m'
WHITE='\033[0;m'

all : $(NAME)

$(NAME) : $(LIBFT) $(PARSING) $(BUILTINS) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PARSING) $(BUILTINS) $(LIBFT) -lreadline
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

$(BUILTINS) :
	@make --directory $(BUILTINS_DIR)

clean :
	@make clean --directory $(LIBFT_DIR)
	@make clean --directory $(PARSING_DIR)
	@make clean --directory $(BUILTINS_DIR)
	@clear
	@$(RM) $(OBJS)
	@echo ${BLUE}">------Files clean-------<\n"${WHITE}

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@$(RM) $(PARSING)
	@$(RM) $(BUILTINS)
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
