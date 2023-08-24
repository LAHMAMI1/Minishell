/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:42:23 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/19 23:37:48 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_list	*get_env_variables(const char **env)
{
	t_list	*new_env;
	char	*tmp_pwd;

	new_env = NULL;
	if (!(*env))
	{
		tmp_pwd = getcwd(NULL, 0);
		ft_lstadd_back(&new_env, ft_lstnew(ft_strjoin("PWD=", tmp_pwd)));
		free(tmp_pwd);
	}
	while (*env)
	{
		ft_lstadd_back(&new_env, ft_lstnew(ft_strdup((char *)*env)));
		env++;
	}
	ft_lstadd_back(&new_env, ft_lstnew(ft_strdup("?=0")));
	return (new_env);
}

char	**convert_linkedlist_to_char_arr(void)
{
	int		size;
	char	**char_array;
	t_list	*current;
	int		i;

	size = ft_lstsize(g_env);
	char_array = (char **)malloc((size + 1) * sizeof(char *));
	if (!char_array)
		return (NULL);
	char_array[size] = NULL;
	current = g_env;
	i = 0;
	while (current != NULL)
	{
		char_array[i] = (char *)(current->content);
		current = current->next;
		i++;
	}
	return (char_array);
}

int	join_and_replace(char *var_name, char *var_value)
{
	char	*join_result;
	int		return_status;

	return_status = 0;
	join_result = ft_strjoin(var_name, var_value);
	return_status = replace_env_var_if_exist(join_result);
	free(join_result);
	return (return_status);
}

int	update_exit_status_var(int status_value)
{
	char	*char_status_value;
	int		return_status;

	return_status = 0;
	char_status_value = ft_itoa(status_value);
	return_status = join_and_replace("?=", char_status_value);
	free(char_status_value);
	return (return_status);
}
