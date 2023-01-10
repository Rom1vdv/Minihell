/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:27:55 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 20:28:48 by yhuberla         ###   ########.fr       */
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

/* opendir */
# include <sys/types.h>
# include <dirent.h>

# include <signal.h>
# include <sys/errno.h>
# include <sys/wait.h>

# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define RED "\033[0;31m"
# define WHITE "\033[0m"
# define YELLOW "\033[0;33m"

typedef struct s_envp {
	char			*head;
	char			*value;
	struct s_envp	*next;
}				t_envp;

typedef struct s_minishell {
	char	**envp_original;
	t_envp	*envp;
}				t_ms;

void	signal_handler(int signo, siginfo_t *info, void *context);

void	lexer(char *rl, t_ms *ms);
int		check_quotes(char *str);
void	exec_echo(char **lex, char *args);
void	exec_cd(char **lex, t_ms *ms);
void	display_pwd(void);
void	exec_export(t_ms *ms, char *line);
void	exec_unset(t_ms *ms, char *target);
void	display_env(t_envp *envp);

void	exec_cmd(char **envp, char *paths, char **cmds);

t_envp	*env_init(char **envp);
char	*ft_getenv(t_envp *envp, char *target);
void	ft_setenv(t_envp *envp, char *target, char *value);

void	set_col(char *col);
void	greet_user(void);
void	close_program(void);

void	ft_perror(char *str);

void	test(void);

#endif
