/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:28:51 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/17 18:13:33 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_handle_redirs(char **rl, t_ms *ms, int piping, int not_last_pipe)
{
	int		index;
	int		sub_index;
	int		len;
	int		append;
	char	*file;

	if (!ft_strchr(*rl, '<') && !ft_strchr(*rl, '>'))
	{
		if (!piping)
			return (lexer(*rl, ms, piping));
		else
			return (exec_pipe(*rl, ms, not_last_pipe));
	}
	index = 0;
	while ((*rl)[index])
	{
		if ((*rl)[index] == '>')
		{
			append = ((*rl)[index + 1] == '>');
			(*rl)[index] = '\0';
			index += append;
			++index;
			while ((*rl)[index] == ' ')
				++index;
			len = 0;
			while ((*rl)[index + len] && (*rl)[index + len] != ' ')
				++len;
			file = ft_malloc(sizeof(*file) * (len + 1), "redirs >");
			sub_index = 0;
			while (sub_index < len)
				file[sub_index++] = (*rl)[index++];
			--index;
			file[sub_index] = '\0';
			if (!append)
				ms->pipeout[1] = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			else
				ms->pipeout[1] = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (ms->pipeout[1] == -1)
				ft_perror("redirs > write");
			exec_pipe(*rl, ms, 0);
			ft_close_pipe(ms->pipein);
			ms->pipein[0] = open(file, O_RDONLY);
			if (ms->pipein[0] == -1)
				ft_perror("redirs > read");
		}
		else if ((*rl)[index] == '<' && (*rl)[index + 1] != '<' && (*rl)[index + 1] != '>')
		{
			(*rl)[index] = '\0';
			++index;
			while ((*rl)[index] == ' ')
				++index;
			len = 0;
			while ((*rl)[index + len] && (*rl)[index + len] != ' ')
				++len;
			file = ft_malloc(sizeof(*file) * (len + 1), "redirs <");
			sub_index = 0;
			while (sub_index < len)
				file[sub_index++] = (*rl)[index++];
			--index;
			file[sub_index] = '\0';
			ms->pipein[0] = open(file, O_RDONLY);
			if (ms->pipein[0] == -1)
				ft_perror("redirs < read");
			exec_pipe(*rl, ms, piping && not_last_pipe);
		}
		else if ((*rl)[index] == '<' && (*rl)[index + 1] == '<')
		{
			(*rl)[index] = '\0';
			index += 2;
			while ((*rl)[index] == ' ')
				++index;
			len = 0;
			while ((*rl)[index + len] && (*rl)[index + len] != ' ')
				++len;
			file = ft_malloc(sizeof(*file) * (len + 1), "redirs <<");
			sub_index = 0;
			while (sub_index < len)
				file[sub_index++] = (*rl)[index++];
			--index;
			file[sub_index] = '\0';
			here_doc(file, ms, *rl);
		}
		else if ((*rl)[index] == '<' && (*rl)[index + 1] == '>')
		{
			(*rl)[index] = '\0';
			index += 2;
			while ((*rl)[index] == ' ')
				++index;
			len = 0;
			while ((*rl)[index + len] && (*rl)[index + len] != ' ')
				++len;
			file = ft_malloc(sizeof(*file) * (len + 1), "redirs <>");
			sub_index = 0;
			while (sub_index < len)
				file[sub_index++] = (*rl)[index++];
			--index;
			file[sub_index] = '\0';
			ms->pipein[0] = open(file, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (ms->pipein[0] == -1)
				ft_perror("redirs <>");
			exec_pipe(*rl, ms, piping && not_last_pipe);
		}
		++index;
	}
}
