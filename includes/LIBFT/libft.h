/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaffard <acaffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:07:47 by acaffard          #+#    #+#             */
/*   Updated: 2024/02/13 13:02:40 by acaffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* PART 1 FUNCTIONS */

/* CHAR ORIENTED FUNCTIONS */

/******************************************************************************
 * FT_ISALPHA :
 * This function checks if the character given is a letter.
 * @params : c -> the character to check
 * @returns : int (1 if True ; 0 if False)
	if (size == 0)
 *****************************************************************************/

int		ft_isalpha(int c);

/******************************************************************************
 * FT_ISDIGIT :
 * This function checks if the character given is a number.
 * @params : c -> the character to check
 * @returns : int (1 if True ; 0 if False)
 *****************************************************************************/

int		ft_isdigit(int c);

/******************************************************************************
 * FT_ISALNUM :
 * This function checks if the character given is a letter or a number.
 * @params : c -> the character to check
 * @returns : int (1 if True ; 0 if False)
 *****************************************************************************/

int		ft_isalnum(int c);

/******************************************************************************
 * FT_ISPRINT :
 * This function checks if the character given is a printable character.
 * @params : c -> the character to check
 * @returns : int (1 if True ; 0 if False)
 *****************************************************************************/

int		ft_isprint(int c);

/******************************************************************************
 * FT_ISASCII :
 * This function checks if the character given is part of the ASCII table.
 * @params : c -> the character to check
 * @returns : int (1 if True ; 0 if False)
 *****************************************************************************/

int		ft_isascii(int c);

/******************************************************************************
 * FT_TOLOWER :
 * This function converts an uppercase character to lowercase.
 * @params : c -> the character to convert
 * @returns : char (The converted character)
 *****************************************************************************/

int		ft_tolower(int c);

/******************************************************************************
 * FT_TOUPPER :
 * This function converts a lowercase character to uppercase.
 * @params : c -> the character to convert
 * @returns : char (The converted character)
 *****************************************************************************/

int		ft_toupper(int c);

/*****************************************************************************/

/* STRING ORIENTED FUNCTIONS */

/******************************************************************************
 * FT_STRLEN :
 * This function detemines the size of the given string.
 * @params : str -> the given string
 * @returns : int (The size of the string)
 *****************************************************************************/

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/* MEMORY ORIENTED FUNCTIONS */
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

void	ft_putchar_fd(int c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new_head);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new_tail);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char	*get_next_line(int fd);

int		ft_putchar_size(int c);
int		ft_putstr_size(char *s);
int		ft_putnbr_base_size(long long n, char	*base, int size);
int		ft_putnbr_ubase_size(unsigned long long n, char	*base, unsigned int s);
int		ft_check_flags(va_list a, const char c);
int		ft_print_hexa(unsigned long long n, char c);
int		ft_printf(const char *s, ...);
#endif