/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:13:48 by olahmami          #+#    #+#             */
/*   Updated: 2023/08/21 17:52:18 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

char	**read_path(char **split_cmds, char **split_path, char *path)
{
	int		i;
	char	*tmp;

	split_path = ft_split_exec(path, ':');
	free(path);
	if (path == NULL)
	{
		ft_free_split(split_path);
		return (split_cmds);
	}
	i = 0;
	while (split_path[i])
	{
		tmp = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], "/");
		free(tmp);
		i++;
	}
	return (split_path);
}

char	**read_env(char **env, char **split_cmds)
{
	char	*path;
	int		len;
	int		i;
	char	**split_path;

	i = 0;
	path = NULL;
	split_path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			len = ft_strlen(env[i]);
			path = ft_substr(env[i], 5, len);
		}
		i++;
	}
	split_path = read_path(split_cmds, split_path, path);
	return (split_path);
}

char	*cmd_extand(char **split_path, char *executable, char **split_cmds)
{
	int	i;

	i = 0;
	while (split_path[i])
	{
		executable = ft_strjoin_exec(split_path[i], split_cmds[0]);
		if (access(executable, F_OK) == 0)
		{
			if (ft_strchr(split_cmds[0], '/'))
				break ;
			return (executable);
		}
		free(executable);
		i++;
	}
	if (access(split_cmds[0], F_OK) == 0 && ft_strchr(split_cmds[0], '/'))
	{
		if (split_path[i] != NULL)
			free(executable);
		executable = split_cmds[0];
	}
	return (executable);
}

void	execution(char **env, char *executable, char **split_cmds)
{
	int	dir;

	if (split_cmds[0] != NULL)
	{
		dir = open(split_cmds[0], __O_DIRECTORY);
		if (dir != -1 && ft_strcmp(split_cmds[0], ""))
			check_directory(split_cmds, dir);
		else if (access(split_cmds[0], F_OK | X_OK) == -1
			&& ft_strchr(split_cmds[0], '/'))
			check_error(split_cmds);
		else if (execve(executable, split_cmds, env) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(split_cmds[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
}

void	global_executor(t_list *list, t_execution *executor)
{
	int		status;
	t_list	*tmp;

	tmp = list;
	status = 0;
	executor->i = 0;
	init_execution(executor, list, &status);
	execute_all_cmd(executor, &status, tmp, list);
	save_and_close(executor);
	waiting(executor, &status);
}
