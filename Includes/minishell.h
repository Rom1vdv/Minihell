/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:27:55 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/26 11:33:35 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include <readline/readline.h>
# include <readline/history.h>

/* opendir */
# include <sys/types.h>
# include <dirent.h>

# include <signal.h>
# include <termios.h>

# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define RED "\033[0;31m"
# define WHITE "\033[0m"
# define YELLOW "\033[0;33m"

# define EXPORT_ERR ": not a valid identifier\n"
# define ISDIR_ERR ": is a directory\n"
# define NOFILE_ERR ": No such file or directory\n"
# define NOTFOUND_ERR ": command not found\n"
# define NUM_ERR ": numeric argument required\n"

typedef enum e_redirs {
	R,
	L,
	RR,
	LL,
	LR
}			t_enum;

typedef struct s_parsing {
	int		parenthesis;
	int		pipe;
	char	quote;
	int		redir;
	int		semicolon;
}				t_parsing;

typedef struct s_redirs {
	int		index;
	int		cpyndex;
	int		findex;
	int		here_doc;
	char	quote;
	char	*file;
}				t_redirs;

typedef struct s_envp {
	char			*key;
	char			*value;
	int				ascii_pos;
	int				exported;
	struct s_envp	*next;
}				t_envp;

typedef struct s_pid {
	int				value;
	struct s_pid	*next;
}				t_pid;

typedef struct s_minishell {
	int		pipein[2];
	int		pipeout[2];
	char	*rl;
	t_envp	*envp;
	t_pid	*pids;
	t_pid	*last_pid;
	char	**pipes;
	char	**semicolons;
	char	**envp_dup;
	int		replace_quotes;
	int		error_file;
	int		error_fork;
}				t_ms;

int	g_ret_cmd;

void	ft_set_signals(int process);

void	lexer(char *rl, t_ms *ms, int index, int piping);
void	prelexer(char *rl, t_ms *ms);
int		check_parse_error(char *str);
void	exec_pipe(char *block, t_ms *ms, int piping);
int		ft_trimquotes(char *str, int index, int cpyndex);
void	swap_quotes_back(char *str);
void	here_doc(char *limiter, t_ms *ms);
void	transform_metachars(t_ms *ms, char *str);
void	ft_joinfree(t_ms *ms, char **str, int *index);
void	ft_joinvar(t_ms *ms, char **str, int *index);

void	ft_handle_redirs(char *rl, t_ms *ms, int piping, int not_last_pipe);
void	redirs_rights(t_redirs *redir, t_ms *ms, char *rl);
void	redirs_left(t_redirs *redir, t_ms *ms, char *rl);
void	redirs_leftleft(t_redirs *redir, t_ms *ms, char *rl);
void	redirs_leftright(t_redirs *redir, t_ms *ms, char *rl);
void	open_file(t_redirs *redir, t_ms *ms, t_enum mode);

void	exec_echo(char **lex);
void	exec_cd(char **lex, t_ms *ms);
void	cd_catpath(char curpath[255], char *directory, t_envp *envp, int index);
void	cd_catpwd(char curpath[255], t_envp *envp);
void	cd_convert_canon(char *curpath);
void	exec_pwd(void);
void	exec_export(t_ms *ms, char **line_array, int exported);
void	exec_unset(t_ms *ms, char **target_array);
void	exec_env(t_envp *envp);
void	exec_exit(char **lex, t_ms *ms, char *rl, int piping);

void	exec_cmd(t_ms *ms, char *path_lst, char **cmds, int infork);
int		ft_fork(t_ms *ms, int *child_pid);
void	ft_pipe(t_ms *ms, int pipefd[2]);
void	ft_close_pipe(int pipefd[2]);
void	ft_set_pipe(int pipefd[2], int in, int out);
void	ft_dup2(int pipefd[2], int fd);

void	ft_wait_child(int pid);
void	ft_addpid(t_ms *ms);
void	ft_wait_pids(t_ms *ms);

t_envp	*env_init(char **envp);
t_envp	*envp_new(char *line, int exported);
char	**env_dup(t_envp *envp);
void	env_setascii(t_envp *envp, t_envp *target);
char	*ft_getenv(t_envp *envp, char *target);
void	ft_setenv(t_envp *envp, char *target, char *value, int exported);
void	ft_setenvpwd(t_envp *envp);
int		ft_envplen(t_envp *envp, int dup);
void	env_increment_shlvl(t_envp *envp);

void	set_col(char *col);
void	greet_user(t_envp *envp);
void	close_program(t_ms *ms, char *rl, char **lex, int piping);
void	ft_stderr(char *str, char *str1, char *str2);

#endif
