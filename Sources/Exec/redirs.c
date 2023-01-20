/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:28:51 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/20 11:40:18 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_handle_redirs(char *rl, t_ms *ms, int piping, int not_last_pipe)
{
	int		index;
	int		sub_index;
	int		len;
	int		append;
	char	save;
	char	quote;
	char	*file;

	ms->file_name = 0;
	if (!ft_strchr_quotes(rl, '<') && !ft_strchr_quotes(rl, '>'))
	{
		// printf("piping : %d, notlast : %d on %s\n", piping, not_last_pipe, rl);
		if (!piping)
			return (lexer(rl, ms, 0));
		else
			return (exec_pipe(rl, ms, not_last_pipe));
	}
	index = 0;
	while (rl[index])
	{
		if (ft_strchr("'\"", rl[index])) // this is used in so many places it needs its own func
		{
			quote = rl[index++];
			while (rl[index] && rl[index] != quote)
				++index;
		}
		save = 0;
		// printf("|%s| at index %d : %c\n\n", rl, index, rl[index]);
		if (rl[index] == '>')
		{
			append = (rl[index + 1] == '>');
			rl[index] = '\0';
			index += append;
			++index;
			while (rl[index] == ' ')
				++index;
			len = 0;
			while (rl[index + len] && !ft_strchr(" <>", rl[index + len]))
			{
				if (ft_strchr("'\"", rl[index + len]))
				{
					quote = rl[index + len++];
					while (rl[index + len] && rl[index + len] != quote)
						++len;
				}
				++len;
			}
			file = ft_malloc(sizeof(*file) * (len + 1), "redirs >");
			sub_index = 0;
			quote = 0;
			while (sub_index < len) // this too deverves its own function
			{
				if (ft_strchr("'\"", rl[index]))
				{
					len -= (!quote || quote == rl[index]);
					if (!quote)
						quote = rl[index];
					else if (quote == rl[index])
						quote = 0;
					else
						file[sub_index++] = rl[index];
				}
				else
					file[sub_index++] = rl[index];
				++index;
			}
			index-=2;
			file[sub_index] = '\0';
			if (!append)
				ms->pipeout[1] = open(file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			else
				ms->pipeout[1] = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (ms->pipeout[1] == -1)
				perror(file);
			// printf("file |%s| cmd |%s|\n", file, rl);
			free(file);
			if (!empty_cmd(rl))
			{
				if (ms->file_name)
				{
					close(ms->pipein[0]);
					ms->pipein[0] = open(ms->file_name, O_RDONLY);
					if (ms->pipein[0] == -1)
					{
						perror(file);
						ft_pipe(ms->pipein);
						g_ret_cmd = 1;
					}
					else
						exec_pipe(rl, ms, 0);
				}
				else
					exec_pipe(rl, ms, 0);
			}
			else
			{
				close(ms->pipeout[1]);
				ms->pipeout[1] = -1;
			}
			if (piping && !ft_strchr(&rl[index], '<') && !ft_strchr(&rl[index], '>'))
			{
				// printf("piping in >, nonno\n");
				ft_pipe(ms->pipein);
				close(ms->pipein[1]);
			}
		}
		else if (rl[index] == '<' && rl[index + 1] != '<' && rl[index + 1] != '>')
		{
			rl[index] = '\0';
			++index;
			while (rl[index] == ' ')
				++index;
			len = 0;
			while (rl[index + len] && rl[index + len] != ' ')
				++len;
			file = ft_malloc(sizeof(*file) * (len + 1), "redirs <");
			sub_index = 0;
			while (sub_index < len)
			{
				if (ft_strchr("'\"", rl[index]))
				{
					len -= (!quote || quote == rl[index]);
					if (!quote)
						quote = rl[index];
					else if (quote == rl[index])
						quote = 0;
					else
						file[sub_index++] = rl[index];
				}
				else
					file[sub_index++] = rl[index];
				++index;
			}
			--index;
			file[sub_index] = '\0';
			if (empty_cmd(rl))
			{
				rl = &rl[index + 1];
				index = 0;
				while (rl[index] &&  rl[index] != '<' && rl[index] != '>')
					++index;
				save = rl[index];
				rl[index] = '\0';
				--index;
			}
			ms->pipein[0] = open(file, O_RDONLY);
			if (ms->pipein[0] == -1)
			{
				perror(file);
				ft_pipe(ms->pipein);
				g_ret_cmd = 1;
			}
			else if (!save)
			{
				// printf("piping %d rl is |%s| empty ? %d\n", not_last_pipe, rl, !empty_cmd(rl));
				if (!empty_cmd(rl) && !ft_strchr(&rl[index], '<') && !ft_strchr(&rl[index], '>'))
					exec_pipe(rl, ms, not_last_pipe);
				else if (!ft_strchr(&rl[index], '>'))
				{
					close(ms->pipein[0]);
					ms->pipein[0] = -1;
				}
				if (!piping && (!ft_strchr(&rl[index], '<') && !ft_strchr(&rl[index], '>')))
				{
					ft_pipe(ms->pipein);
					close(ms->pipein[1]);
				}
				// exec_pipe(rl, ms, piping && not_last_pipe);
			}
			ms->file_name = file;
			// printf("save = %c\n", save);
			if (save)
				rl[index + 1] = save;
		}
		else if (rl[index] == '<' && rl[index + 1] == '<')
		{
			rl[index] = '\0';
			index += 2;
			while (rl[index] == ' ')
				++index;
			len = 0;
			while (rl[index + len] && rl[index + len] != ' ')
				++len;
			file = ft_malloc(sizeof(*file) * (len + 1), "redirs <<");
			sub_index = 0;
			while (sub_index < len)
				file[sub_index++] = rl[index++];
			--index;
			file[sub_index] = '\0';
			here_doc(file, ms, rl, not_last_pipe);
		}
		else if (rl[index] == '<' && rl[index + 1] == '>')
		{
			rl[index] = '\0';
			index += 2;
			while (rl[index] == ' ')
				++index;
			len = 0;
			while (rl[index + len] && rl[index + len] != ' ')
				++len;
			file = ft_malloc(sizeof(*file) * (len + 1), "redirs <>");
			sub_index = 0;
			while (sub_index < len)
				file[sub_index++] = rl[index++];
			--index;
			file[sub_index] = '\0';
			ms->pipein[0] = open(file, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if (ms->pipein[0] == -1)
				perror(file);
			exec_pipe(rl, ms, piping && not_last_pipe);
		}
		++index;
	}
}
