/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:35:24 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/25 15:12:18 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	display_sorted_env(t_envp *envp)
{
	int		index;
	int		size;
	t_envp	*tmp;

	size = ft_envplen(envp, 0);
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
				printf("declare -x %s\n", tmp->key);
		}
		++index;
	}
}

static void	ft_exportvar(t_envp *envp, char *target, int targetlen)
{
	char	*join;
	t_envp	*tmp;

	if (!envp || !target)
		return ;
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
			join = ft_strdup(target);
			tmp->next = envp_new(join, -1);
			env_setascii(envp, tmp->next);
			return (free(join));
		}
	}
}

static int	valid_key(char *line, char *key, int keylen, int exported)
{
	if (!keylen || ft_strchr("0123456789=", key[0]) || ft_strchr(key, '-')
		|| ft_strchr(key, '\\') || ft_strchr(key, '.') || ft_strchr(key, '+')
		|| ft_strchr(key, '$') || ft_strchr(key, '}') || ft_strchr(key, '{')
		|| ft_strchr(key, '*') || ft_strchr(key, '#') || ft_strchr(key, '@')
		|| ft_strchr(key, '!') || ft_strchr(key, '^') || ft_strchr(key, '~')
		|| ft_strchr(key, ':'))
	{
		free(key);
		if (exported)
		{
			ft_stderr("-minishell: export: ", line, EXPORT_ERR);
			g_ret_cmd = 1 + (line[0] == '-');
		}
		else
		{
			if (line[0] == '.')
				ft_stderr("-minishell: ", line, NOFILE_ERR);
			else
				ft_stderr("-minishell: ", line, NOTFOUND_ERR);
			g_ret_cmd = 127;
		}
		return (0);
	}
	return (1);
}

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
	if (!valid_key(line, key, keylen, exported))
		return ;
	if (!value)
	{
		ft_exportvar(ms->envp, line, ft_strlen(line) + 1);
		return (free(key));
	}
	ft_setenv(ms->envp, key, &value[1], exported);
	free(key);
}

void	exec_export(t_ms *ms, char **line_array, int exported)
{
	int	index;

	index = 0;
	if (!ms || !ms->envp)
		return ;
	g_ret_cmd = 0;
	if (!line_array[0])
	{
		display_sorted_env(ms->envp);
		return ;
	}
	while (line_array[index])
	{
		handle_export_args(ms, line_array[index], exported);
		++index;
	}
}
