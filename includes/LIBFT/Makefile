# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 12:04:03 by antoine           #+#    #+#              #
#    Updated: 2024/05/16 13:35:32 by acaffard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_memcmp.c \
		ft_strncmp.c \
		ft_memmove.c \
		ft_atoi.c \
		ft_strdup.c \
		ft_strnstr.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line.c \
		ft_printf.c \
		ft_putchar_size.c \
		ft_putnbr_ubase_size.c \
		ft_putnbr_base_size.c \
		ft_check_flags.c \
		ft_putstr_size.c \
		ft_print_hexa.c \
		ft_free_stringtab.c \
		ft_stringtab_len.c \
		ft_print_stringtab.c \
		ft_split_str.c \
		ft_lst_remove_index.c \
		ft_lst_get_index.c\
		count_occurences_in_string.c\
		ft_string_isdigit.c\
		ft_strndup.c\
		locate_string_in_stringtab.c
CC = cc
NAME = libft.a
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror

%.o : %.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all
