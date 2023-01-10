/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:27:55 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 13:16:09 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../Libft/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>

# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define RED "\033[0;31m"
# define WHITE "\033[0m"
# define YELLOW "\033[0;33m"

typedef struct s_minishell {
	char	*prev_pwd;//[255];
	char	**envp;
}				t_ms;

void	signal_handler(int signo, siginfo_t *info, void *context);

void	lexer(char *rl, t_ms *ms);
int		check_quotes(char *str);
void	exec_echo(char **lex, char *args);
void	exec_cd(char **lex, t_ms *ms);
void	display_pwd(void);
void	display_env(char **envp);

void	set_col(char *col);
void	greet_user(void);
void	close_program(void);

void	ft_perror(char *str);

void	test(void);

#endif
