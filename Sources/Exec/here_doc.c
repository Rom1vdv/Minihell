/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:22:32 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/24 18:05:38 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	transform_meta_heredoc(t_ms *ms, char *str, int quotes)
{
	int		index;

	ms->rl = NULL;
	index = 0;
	while (str[index])
	{
		if (str[index] == '$' && str[index + 1] != ' ' && str[index + 1]
			&& !quotes)
			ft_joinvar(ms, &str, &index);
		else
			++index;
	}
	ft_joinfree(ms, &str, &index);
}

static int	ft_trimquotes(char *str, int index, int cpyndex)
{
	int		res;
	char	quote;

	res = 0;
	quote = 0;
	while (str[index])
	{
		if (ft_strchr("'\"", str[index]))
		{
			res = 1;
			if (!quote)
				quote = str[index];
			else if (str[index] == quote)
				quote = 0;
			else
				str[cpyndex++] = str[index];
		}
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
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1))
			break ;
		transform_meta_heredoc(ms, line, quotes);
		write(fd, ms->rl, ft_strlen(ms->rl));
		write(fd, "\n", 1);
		free(ms->rl);
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

void	here_doc(char *limiter, t_ms *ms)
{
	int		fd;
	int		quotes;

	quotes = ft_trimquotes(limiter, 0, 0);
	fd = open(".here_doc_tmp", O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		ft_perror("here_doc");
	here_doc_loop(limiter, fd, ms, quotes);
	close(fd);
}
