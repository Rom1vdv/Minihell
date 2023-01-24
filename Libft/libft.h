/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:41:11 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/24 17:14:44 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 42
// # endif

// # include <unistd.h>
# include <stdlib.h>
// # include <limits.h>
# include <stdarg.h>

void	ft_perror(char *str);
void	*ft_malloc(int size, char *msg);
// int		ft_max(int a, int b);
// int		ft_min(int a, int b);
// int		ft_abs(int nb);
void	ft_bzero(void *s, size_t n);
void	ft_free_arr(char **arr);

int		ft_atoi(const char *str);
int		ft_atoi_64bits(char *str);
char	*ft_itoa(int n);
// void	ft_arrayset(int *tab, int value, int size);
// int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strchr_quotes(char *str, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_strcpy(char *dst, const char *src);
void	ft_strcat(char *dst, const char *src);
// char	*get_next_line(int fd);
// char	*ft_strjoin_gnl(char *s1, char *s2);
// char	*ft_strdup_gnl(char **str);
// char	*ft_strcpy_from_nl(char **str);
// char	*ft_strcpy_until_nl(char *str);

size_t	ft_strlen(const char *str);
// char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	**ft_split_quotes(char *str, char c);
char	**ft_split_first(char const *s, char c);
char	**ft_split_quotes_set(char const *s, char *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoins(int ac, ...);
char	*ft_strdup(const char *s1);
// char	**ft_arrayadd_back(char **arr, char *str);
int		ft_arraylen(char **array);

// void		ft_printf(const char *str, ...);
// int		ft_abs(int nb);
// int		ft_nbrlen(int nb);
// char	ft_get_type(char c);
// void	ft_putchar(unsigned char c);
// void	ft_putchars(unsigned char c, int size);
void	ft_putendl(char *s);
// void	ft_putstr_fd(char *str, int fd);
// void	ft_putnbr(int nb);
// void	ft_putunbr(unsigned int nb);
// void	ft_puthexa(unsigned int nb, int upper);
// void	ft_putaddresshexa(void *ptr);

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }				t_list;

// void	ft_lstadd_back(t_list **lst, t_list *new);
// void	ft_lstdelone(t_list *lst, void (*del)(void *));
// void	ft_lstclear(t_list **lst, void (*del)(void *));
// t_list	*ft_lstnew(void *content);

#endif
