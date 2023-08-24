/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:19:47 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/18 11:19:55 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_builtin(t_cmd_file cmd_file)
{
	t_list	*list;

	list = cmd_file.cmds;
	if (!list)
		return (0);
	if (ft_strcmp(list->content, "echo") == 0)
		return (1);
	else if (ft_strcmp(list->content, "export") == 0)
		return (1);
	else if (ft_strcmp(list->content, "unset") == 0)
		return (1);
	else if (ft_strcmp(list->content, "env") == 0)
		return (1);
	else if (ft_strcmp(list->content, "pwd") == 0)
		return (1);
	else if (ft_strcmp(list->content, "exit") == 0)
		return (1);
	else if (ft_strcmp(list->content, "cd") == 0)
		return (1);
	else
		return (0);
}

int	builtin(t_cmd_file cmd_file, int *flag)
{
	t_list	*list;

	list = cmd_file.cmds;
	*flag = 1;
	if (!list)
		return (0);
	if (ft_strcmp(list->content, "echo") == 0)
		return (ft_echo(list));
	if (ft_strcmp(list->content, "export") == 0)
		return (ft_export(list));
	if (ft_strcmp(list->content, "unset") == 0)
		return (ft_unset(list));
	if (ft_strcmp(list->content, "env") == 0)
		return (ft_env(list));
	if (ft_strcmp(list->content, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(list->content, "exit") == 0)
		return (ft_exit(list));
	if (ft_strcmp(list->content, "cd") == 0)
		return (ft_cd(list));
	return (0);
}
