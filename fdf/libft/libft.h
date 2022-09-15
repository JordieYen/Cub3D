/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 12:47:37 by jking-ye          #+#    #+#             */
/*   Updated: 2021/07/19 18:18:54 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int				ft_atoi(const char *str);
void			*ft_memset(char *str, int c, unsigned int n);
void			ft_bzero(char *str, unsigned int n);
void			*ft_memcpy(void *dest, const void *src, unsigned int n);
void			*ft_memccpy(void *s1, const void *s2, char c, size_t n);
void			*ft_memmove(void *dest, const void *src, unsigned int n);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const char *s1, const char *s2, size_t n);
int				ft_strlen(const void *str);
unsigned long	ft_strlcpy(void *dest, const void *src, unsigned int l);
unsigned long	ft_strlcat(void *dest, const void *src, unsigned int l);
char			*ft_strchr(const char *str, int chr);
char			*ft_strrchr(char *str, int c);
char			*ft_strnstr(char *hay, const char *needle, unsigned int n);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_calloc(size_t nitems, size_t size);
char			*ft_strdup(char *s);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(const void *s1, const void *s2);
char			*ft_strtrim(char const *s, char const *set);
char			**ft_split(const char *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

#endif
