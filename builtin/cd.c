/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:29:39 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 16:31:00 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	update_path(char *old_path, const char *pwd)
{
	if (get_env_var_value("PWD") && pwd)
		join_and_replace("PWD=", (char *)pwd);
	if (get_env_var_value("OLDPWD") && old_path)
		join_and_replace("OLDPWD=", old_path);
}

int	cd_oldpwd(char *oldpath_value)
{
	const char	*pwd;

	pwd = get_env_var_value("OLDPWD");
	if (pwd)
	{
		chdir(pwd);
		ft_putendl_fd((char *)pwd, 1);
		update_path(oldpath_value, pwd);
		return (SUCCESS);
	}
	else
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (ERROR);
	}
}

int	cd_home(char *oldpath_value)
{
	const char	*home_path;

	home_path = get_env_var_value("HOME");
	if (home_path)
	{
		chdir(home_path);
		update_path(oldpath_value, home_path);
		return (SUCCESS);
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (ERROR);
	}
}

int	cd_path(char *go_to_path, char *oldpath_value)
{
	int		to_be_returnd;
	char	*pwd;

	pwd = NULL;
	to_be_returnd = SUCCESS;
	if (chdir(go_to_path) == 0)
	{
		pwd = getcwd(NULL, 0);
		update_path(oldpath_value, pwd);
		free(pwd);
	}
	else
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		free(pwd);
		to_be_returnd = ERROR;
	}
	return (to_be_returnd);
}

int	ft_cd(t_list *list)
{
	char	*oldpath_value;
	int		to_be_returnd;

	to_be_returnd = 0;
	oldpath_value = NULL;
	oldpath_value = getcwd(oldpath_value, 0);
	if (ft_lstsize(list) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		free(oldpath_value);
		return (ERROR);
	}
	if (ft_lstsize(list) == 1 || ft_strcmp(list->next->content, "~") == 0)
		to_be_returnd = cd_home(oldpath_value);
	else if (ft_strcmp("-", list->next->content) == 0)
		to_be_returnd = cd_oldpwd(oldpath_value);
	else
		to_be_returnd = cd_path(list->next->content, oldpath_value);
	free(oldpath_value);
	return (to_be_returnd);
}
