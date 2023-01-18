/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:22:32 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/18 11:47:52 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	transform_metachars(t_ms *ms, char *str, int quotes)
{
	int		index;

	ms->rl = NULL;
	index = 0;
	while (str[index])
	{
		// printf("%d : %c\n", index, str[index]);
		if (str[index] == '$' && str[index + 1] != ' ' && str[index + 1] && !quotes)
			ft_joinvar(ms, &str, &index, 0);
		else
			++index;
	}
	ft_joinfree(ms, &str, &index);
}

static int	ft_trimquotes(char *str)
{
	int	res;
	int	index;
	int	cpyndex;

	index = 0;
	cpyndex = 0;
	res = 0;
	while (str[index])
	{
		if (ft_strchr("'\"", str[index]))
			res = 1;
		else
			str[cpyndex++] = str[index];
		++index;
	}
	str[cpyndex] = '\0';
	return (res);
}

static void	here_doc_loop(char *limiter, int fd, t_ms *ms, int quotes)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			ft_perror("gnl");
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1))
			break ;
		transform_metachars(ms, line, quotes);
		write(fd, ms->rl, ft_strlen(ms->rl));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}

int	empty_cmd(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] != ' ')
			return (0);
		++index;
	}
	return (1);
}

void	here_doc(char *limiter, t_ms *ms, char *rl, int piping)
{
	int		fd;
	int		quotes;

	quotes = ft_trimquotes(limiter);
	fd = open(".here_doc_tmp", O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		ft_perror("here_doc");
	here_doc_loop(limiter, fd, ms, quotes);
	close(fd);
	ms->pipein[0] = open(".here_doc_tmp", O_RDONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (ms->pipein[0] < 0)
	{
		unlink(".here_doc_tmp");
		ft_perror("here_doc");
	}
	if (!empty_cmd(rl))
		exec_pipe(rl, ms, piping);
	else
		exec_pipe("cat", ms, piping);
	unlink(".here_doc_tmp");
}
