/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:27:55 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/18 16:30:34 by romvan-d         ###   ########.fr       */
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
#include <sys/stat.h>
#include <fcntl.h>

# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define RED "\033[0;31m"
# define WHITE "\033[0m"
# define YELLOW "\033[0;33m"

typedef struct s_envp {
	char	*key;
	char	*value;
	int		ascii_pos;
	int		exported;
	struct s_envp	*next;
}				t_envp;

typedef struct s_minishell {
	int		ret_cmd;
	int		pipein[2];
	int		pipeout[2];
	char	*file_name;
	char	*rl;
	char	**envp_original;
	t_envp	*envp;
}				t_ms;

void	signal_handler(int signo, siginfo_t *info, void *context);

void	lexer(char *rl, t_ms *ms, int piping);
void	lexer_bonus(char *rl, t_ms *ms);
void	ft_handle_redirs(char *rl, t_ms *ms, int piping, int not_last_pipe);
void	exec_pipe(char *block, t_ms *ms, int piping);
void	here_doc(char *limiter, t_ms *ms, char *rl, int piping);
int		empty_cmd(char *str);
void	ft_joinfree(t_ms *ms, char **strptr, int *index);
void	ft_joinvar(t_ms *ms, char **strptr, int *index, char quote);

void	exec_echo(char **lex, int *ret_cmd);
void	exec_cd(char **lex, t_ms *ms);
void	exec_pwd(int *ret_cmd);
void	exec_export(t_ms *ms, char *line, int exported);
void	exec_unset(t_ms *ms, char *target);
void	exec_env(t_envp *envp, int *ret_cmd);
void	exec_exit(char **lex, t_ms *ms, char *rl, int piping);

void	exec_cmd(int *ret_cmd, char **envp, char *path_lst, char **cmds);
void	ft_wait_child(int pid, int *ret_cmd);
void	ft_fork(int *child_pid);
void	ft_pipe(int pipefd[2]);
void	ft_close_pipe(int pipefd[2]);
void	ft_set_pipe(int pipefd[2], int in, int out);
void	ft_dup2(int pipefd[2], int fd);

t_envp	*env_init(char **envp);
t_envp	*envp_new(char *line, int exported);
char	**env_dup(t_envp *envp);
void	env_setascii(t_envp *envp, t_envp *target);
char	*ft_getenv(t_envp *envp, char *target);
void	ft_setenv(t_envp *envp, char *target, char *value, int exported);
void	ft_setenvpwd(t_envp *envp);
int		ft_envplen(t_envp *envp);
void	env_increment_shlvl(t_envp *envp);

void	set_col(char *col);
void	greet_user(t_envp *envp);
void	close_program(t_ms *ms, char *rl, char **lex, int piping);

void	test(t_ms *ms);

#endif
