/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:35:24 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/21 15:48:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	display_sorted_env(t_envp *envp)
{
	int		index;
	int		size;
	t_envp	*tmp;

	size = ft_envplen(envp);
	index = 1;
	while (index < size + 1)
	{
		tmp = envp;
		while (tmp && tmp->ascii_pos != index)
			tmp = tmp->next;
		if (tmp && ft_strncmp(tmp->key, "_", 2))
		{
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			else
				printf("declare -x %s=\"\"\n", tmp->key);
		}
		++index;
	}
}

static void	ft_exportvar(t_envp *envp, char *target)
{
	int		targetlen;
	char	*join;
	t_envp	*tmp;

	if (!envp || !target)
		return ;
	targetlen = ft_strlen(target) + 1;
	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, target, targetlen))
		{
			tmp->exported = 1;
			env_setascii(envp, tmp);
			return ;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			join = ft_strjoin(target, "=");
			tmp->next = envp_new(join, 1);
			env_setascii(envp, tmp->next);
			return (free(join));
		}
	}
}

// static void	ft_trimquotes(char *value) //did this for nothing
// {
// 	int		index;
// 	int		cpyndex;
// 	char	quote;

// 	index = 1;
// 	cpyndex = 1;
// 	quote = 0;
// 	while (value[index])
// 	{
// 		if (ft_strchr("'\"", value[index]))
// 		{
// 			if (!quote)
// 				quote = value[index];
// 			else if (value[index] == quote)
// 				quote = 0;
// 			else
// 				value[cpyndex++] = value[index];
// 		}
// 		else
// 			value[cpyndex++] = value[index];
// 		++index;
// 	}
// 	value[cpyndex] = '\0';
// }

static void	handle_export_args(t_ms *ms, char *line, int exported)
{
	int		keylen;
	char	*value;
	char	*key;

	value = ft_strchr(line, '=');
	key = ft_strdup(line);
	key[ft_strlen(line) - ft_strlen(value)] = '\0';
	keylen = ft_strlen(key);
	if (keylen > 1 && key[keylen - 1] == '+')
	{
		exported += 2;
		key[keylen - 1] = '\0';
		--keylen;
	}
	if (!keylen || ft_strchr("0123456789=", key[0]) || ft_strchr(key, '-') || ft_strchr(key, '\\') || ft_strchr(key, '.')
			|| ft_strchr(key, '+') || ft_strchr(key, '$') || ft_strchr(key, '}') || ft_strchr(key, '{') || ft_strchr(key, '*')
			|| ft_strchr(key, '#') || ft_strchr(key, '@') || ft_strchr(key, '!') || ft_strchr(key, '^') || ft_strchr(key, '~'))
	{
		free(key);
		if (exported)
		{
			write(2, "-minishell: export: '", 21);
			write(2, line, ft_strlen(line));
			write(2, "': not a valid indentifier\n", 27);
			g_ret_cmd = 1 + (line[0] == '-');
		}
		else
		{
			write(2, "-minishell: '", 13);
			write(2, line, ft_strlen(line));
			write(2, "': command not found\n", 21);
			g_ret_cmd = 127;
		}
		return ;
	}
	g_ret_cmd = 0;
	if (!value)
	{
		ft_exportvar(ms->envp, line);
		return ;
	}
	// ft_trimquotes(value);
	ft_setenv(ms->envp, key, &value[1], exported);
	free(key);
}

void	exec_export(t_ms *ms, char **line_array, int exported)
{
	int	index;

	index = 0;
	if (!ms || !ms->envp)
		return ;
	if (!line_array[0])
	{
		display_sorted_env(ms->envp);
		return ;
	}
	while(line_array[index])
	{
		handle_export_args(ms, line_array[index], exported);
		++index;
	}
	
}
