/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:43:45 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/23 08:43:45 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	parse_error(char *str, char c)
{
	write(2, "-minishell: parse error : ", 27);
	if (str)
		write(2, str, ft_strlen(str));
	else
		write(2, &c, 1);
	write(2, "\n", 1);
	return (1);
}

static int	semicolons_pipes(t_parsing *parse, char c)
{
	if (c == ';')
	{
		if (!parse->semicolon)
			return (parse_error("';'", 0));
		parse->semicolon = 0;
	}
	else if (c != ' ')
		parse->semicolon = 1;
	if (c == '|')
	{
		if (parse->pipe)
			return (parse_error("'|'", 0));
		parse->pipe = 1;
	}
	else if (c != ' ')
		parse->pipe = 0;
	return (0);
}

static int	quotes_redirs_parenthesis(t_parsing *parse, char *str, int *index)
{
	if (ft_strchr("'\"", str[*index]))
	{
		parse->quote = str[(*index)++];
		while (str[*index] && str[*index] != parse->quote)
			++(*index);
		if (!str[*index])
			return (parse_error("quotes", 0));
	}
	if (ft_strchr("><", str[*index]))
	{
		if (parse->redir && (((parse->redir > 0) && (str[*index] == '<'))
				|| (*index > 0 && str[*index - 1] == ' ')))
			return (parse_error(0, str[*index]));
		parse->redir += (str[*index] == '>') - (str[*index] == '<');
		if (parse->redir * (1 - 2 * (parse->redir < 0)) > 2)
			return (parse_error(0, str[*index]));
	}
	else if (!ft_strchr("<> ", str[*index]))
		parse->redir = 0;
	if (str[*index] == ')' && !parse->parenthesis)
		return (parse_error("parenthesis", 0));
	parse->parenthesis += (str[*index] == '(') - (str[*index] == ')');
	return (semicolons_pipes(parse, str[*index]));
}

int	check_parse_error(char *str)
{
	int			index;
	t_parsing	parse;

	parse.parenthesis = 0;
	parse.pipe = -1;
	parse.redir = 0;
	parse.semicolon = 0;
	index = 0;
	while (str[index])
	{
		if (quotes_redirs_parenthesis(&parse, str, &index))
			return (1);
		++index;
	}
	if (parse.parenthesis)
		return (parse_error("parenthesis", 0));
	if (parse.pipe == 1)
		return (parse_error("'|'", 0));
	if (parse.redir)
		return (parse_error(0, "<>"[parse.redir > 0]));
	return (0);
}
