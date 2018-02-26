/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquenel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 15:15:15 by jquenel           #+#    #+#             */
/*   Updated: 2017/12/16 04:55:56 by jquenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <inttypes.h>
# include "ft_printf.h"
# include "get_next_line.h"

/*
**		,===================================================================,
**		|                                                                   |
**		|                       WELCOME TO THIS LIBFT                       |
**		|                                                                   |
**		|                                                                   |
**		|   This lib is still in progress, and will be updated regularly    |
**		|                                                                   |
**		|   Latest changes :    +ft_putchar UTF-8 compatibility             |
**		|                       +ft_itoa_base                               |
**		|                       +get_next_line                              |
**		|                                                                   |
**		|   Current work in progress :  ft_printf                           |
**		|                                                                   |
**		|   TO_DO :     optimize the basic function of libft                |
**		|                                                                   |
**		'==================================================================='
*/

/*
**         SOME STRUCTS
*/

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

/*
**         TYPE >> TYPE FAMILY
*/

int				ft_atoi(char const *s);
long			ft_atol(char const *s);
char			*ft_itoa(intmax_t n);
char			*ft_itoa_base(intmax_t n, char *bset);
char			*ft_uitoa(uintmax_t n);
char			*ft_uitoa_base(uintmax_t n, char *bset);

/*
**         PUT FAMILY
*/

int				ft_putchar(int c);
int				ft_putstr(const char *s);
int				ft_putnbr(const int nb);
int				ft_putendl(char const *s);
int				ft_putchar_fd(int c, int fd);
int				ft_putstr_fd(char const *s, int fd);
int				ft_putendl_fd(char const *s, int fd);
int				ft_putnbr_fd(int n, int fd);
int				ft_putbits(unsigned char c);
int				ft_putbits_fd(unsigned char c, int fd);

/*
**			STR FAMILY
*/

size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_tabdel(void *tab);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s3, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmerge(char *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			*ft_strstr(char const *haystack, char const *needle);
char			*ft_strnstr(char const *haystack, char const *needle,
							size_t len);
char			**ft_strsplit(char const *s, char c);
size_t			ft_strcspn(const char *s, const char *charset);
char			*ft_strndup(const char *s1, size_t n);
int				ft_stris();

size_t			ft_intlen(int n);

/*
**			MEM FAMILY
*/

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
int				ft_memjoin(void **s1, void *s2, size_t n1, size_t n2);
int				ft_memrjoin(void **s1, void *s2, size_t n1, size_t n2);

/*
**			CHARTYPE FAMILY
*/

int				ft_stris(char const *str, int (*f)(int));
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);

/*
**			LOW/UPCASE FAMILY
*/

int				ft_toupper(int c);
int				ft_tolower(int c);

/*
**			LIST FAMILY
*/

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **lst, t_list *newl);
void			ft_lstpushback(t_list **lst, t_list *newl);
void			ft_lstinsert(t_list *prev, t_list *newl);
size_t			ft_lstlen(t_list *lst);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));

#endif
