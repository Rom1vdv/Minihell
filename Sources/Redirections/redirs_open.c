/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:23:10 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/25 17:14:59 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	open_file_left(t_redirs *redir, t_ms *ms, t_enum mode)
{
	if (ms->pipein[0] != -1)
	{
		ft_close_pipe(ms->pipein);
		if (redir->here_doc && mode == L)
		{
			redir->here_doc = 0;
			unlink(".here_doc_tmp");
		}
	}
	if (mode == L)
		ms->pipein[0] = open(redir->file, O_RDONLY);
	else
		ms->pipein[0] = open(".here_doc_tmp", O_RDONLY);
	if (ms->pipein[0] == -1 && mode == LL)
	{
		ms->error_file = 1;
		redir->here_doc = 0;
		unlink(".here_doc_tmp");
		perror("here_doc");
	}
	else if (ms->pipein[0] == -1)
	{
		ms->error_file = 1;
		perror(redir->file);
	}
}

static void	open_file_right(t_redirs *redir, t_ms *ms, t_enum mode)
{
	if (ms->pipeout[1] != -1)
		ft_close_pipe(ms->pipeout);
	if (mode == R)
		ms->pipeout[1] = open(redir->file, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		ms->pipeout[1] = open(redir->file, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (ms->pipeout[1] == -1)
	{
		ms->error_file = 1;
		perror(redir->file);
	}
}

void	open_file(t_redirs *redir, t_ms *ms, t_enum mode)
{
	if ((mode == R || mode == RR))
		open_file_right(redir, ms, mode);
	else if (mode == L || mode == LL)
		open_file_left(redir, ms, mode);
}
