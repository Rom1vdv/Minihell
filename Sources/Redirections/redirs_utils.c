/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:28:54 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/26 12:05:20 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	redirs_getfile(t_redirs *red, t_ms *ms, char *rl)
{
	int	len;

	len = 0;
	while (rl[red->index + len] && !ft_strchr(" <>", rl[red->index + len]))
	{
		if (ft_strchr("'\"", rl[red->index + len]))
		{
			red->quote = rl[red->index + len++];
			while (rl[red->index + len] && rl[red->index + len] != red->quote)
				++len;
		}
		++len;
	}
	red->file = ft_malloc(sizeof(*red->file) * (len + 1), "redirs");
	red->findex = 0;
	while (red->findex < len)
	{
		red->file[red->findex] = rl[red->index];
		++red->findex;
		++red->index;
	}
	red->file[red->findex] = '\0';
	--red->index;
	ms->replace_quotes = 1;
	transform_metachars(ms, red->file);
}

void	redirs_rights(t_redirs *redir, t_ms *ms, char *rl)
{
	t_enum	mode;

	++redir->index;
	mode = R;
	if (rl[redir->index] == '>')
	{
		++redir->index;
		mode = RR;
	}
	while (rl[redir->index] == ' ')
		++redir->index;
	redirs_getfile(redir, ms, rl);
	ft_trimquotes(ms->rl, 0, 0);
	swap_quotes_back(ms->rl);
	free(redir->file);
	redir->file = ms->rl;
	open_file(redir, ms, mode);
	free(ms->rl);
}

void	redirs_left(t_redirs *redir, t_ms *ms, char *rl)
{
	++redir->index;
	while (rl[redir->index] == ' ')
		++redir->index;
	redirs_getfile(redir, ms, rl);
	ft_trimquotes(ms->rl, 0, 0);
	swap_quotes_back(ms->rl);
	free(redir->file);
	redir->file = ms->rl;
	open_file(redir, ms, L);
	free(ms->rl);
}

void	redirs_leftleft(t_redirs *redir, t_ms *ms, char *rl)
{
	redir->index += 2;
	while (rl[redir->index] == ' ')
		++redir->index;
	redirs_getfile(redir, ms, rl);
	free(redir->file);
	redir->file = ms->rl;
	here_doc(redir->file, ms);
	free(redir->file);
	open_file(redir, ms, LL);
	redir->here_doc = 1;
}

void	redirs_leftright(t_redirs *redir, t_ms *ms, char *rl)
{
	int	fd;

	redir->index += 2;
	while (rl[redir->index] == ' ')
		++redir->index;
	redirs_getfile(redir, ms, rl);
	ft_trimquotes(ms->rl, 0, 0);
	swap_quotes_back(ms->rl);
	free(redir->file);
	redir->file = ms->rl;
	fd = open(redir->file, O_WRONLY | O_APPEND | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		ms->error_file = 1;
		return ;
	}
	close(fd);
	open_file(redir, ms, L);
	free(ms->rl);
}
