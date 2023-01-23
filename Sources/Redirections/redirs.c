/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:56:27 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/23 11:01:58 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	redirs_quote(t_redirs *redir, char *rl)
{
	if (ft_strchr("'\"", rl[redir->index]))
	{
		redir->quote = rl[redir->index];
		++redir->index;
		while (rl[redir->index] && rl[redir->index] != redir->quote)
		{
			rl[redir->cpyndex] = rl[redir->index];
			++redir->cpyndex;
			++redir->index;
		}	
		return (1);
	}
	return (0);
}

static int	redirs_main(t_redirs *redir, t_ms *ms, char *rl)
{
	if (rl[redir->index] == '>')
		redirs_rights(redir, ms, rl);
	else if (rl[redir->index] == '<'
		&& rl[redir->index + 1] != '<' && rl[redir->index + 1] != '>')
		redirs_left(redir, ms, rl);
	else if (rl[redir->index] == '<' && rl[redir->index + 1] == '<')
		redirs_leftleft(redir, ms, rl);
	else if (rl[redir->index] == '<' && rl[redir->index + 1] == '>')
		redirs_leftright(redir, ms, rl);
	else
		return (0);
	return (1);
}

void	ft_handle_redirs(char *rl, t_ms *ms, int piping, int not_last_pipe)
{
	t_redirs	redir;

	if (!ft_strchr_quotes(rl, '<') && !ft_strchr_quotes(rl, '>'))
	{
		if (!piping)
			return (lexer(rl, ms, 0, 0));
		else
			return (exec_pipe(rl, ms, not_last_pipe));
	}
	redir.here_doc = 0;
	redir.index = 0;
	redir.cpyndex = 0;
	while (rl[redir.index])
	{
		if (redirs_quote(&redir, rl))
			;
		else if (redirs_main(&redir, ms, rl))
			;
		else
			rl[redir.cpyndex++] = rl[redir.index];
		++redir.index;
	}
	rl[redir.cpyndex] = '\0';
	if (!empty_cmd(rl))
	{
		if (ms->pipeout[1] != -1)
		{
			exec_pipe(rl, ms, 0);
			ft_pipe(ms->pipein);
			close(ms->pipein[1]);
		}
		else
			exec_pipe(rl, ms, not_last_pipe);
	}
	if (redir.here_doc)
		unlink(".here_doc_tmp");
}
