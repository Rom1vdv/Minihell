/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:28:54 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/23 10:58:51 by yhuberla         ###   ########.fr       */
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
	transform_metachars(ms, red->file);
	free(red->file);
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
	open_file(redir, ms, mode);
	free(ms->rl);
}

void	redirs_left(t_redirs *redir, t_ms *ms, char *rl)
{
	++redir->index;
	while (rl[redir->index] == ' ')
		++redir->index;
	redirs_getfile(redir, ms, rl);
	open_file(redir, ms, L);
	free(ms->rl);
}

void	redirs_leftleft(t_redirs *redir, t_ms *ms, char *rl)
{
	int		len;

	redir->index += 2;
	while (rl[redir->index] == ' ')
		++redir->index;
	len = 0;
	while (rl[redir->index + len] && !ft_strchr(" <>", rl[redir->index + len]))
		++len;
	redir->file = ft_malloc(sizeof(*redir->file) * (len + 1), "redirs <<");
	redir->findex = 0;
	while (redir->findex < len)
		redir->file[redir->findex++] = rl[redir->index++];
	--redir->index;
	redir->file[redir->findex] = '\0';
	here_doc(redir->file, ms);
	free(redir->file);
	open_file(redir, ms, LL);
	redir->here_doc = 1;
}

void	redirs_leftright(t_redirs *redir, t_ms *ms, char *rl)
{
	redir->index += 2;
	while (rl[redir->index] == ' ')
		++redir->index;
	redirs_getfile(redir, ms, rl);
	open_file(redir, ms, L);
	free(ms->rl);
}
