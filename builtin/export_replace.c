/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:37:51 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 13:46:15 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int	var_was_replace_or_join(char *str, int plus_index)
{
	t_list	*tmp;
	char	*tmp_content;

	tmp = g_env;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, str, plus_index) == 0
			&& ((char *)tmp->content)[plus_index] == '=')
		{
			tmp_content = tmp->content;
			tmp->content = ft_strjoin(tmp->content, str + plus_index + 2);
			free(tmp_content);
			return (1);
		}
		if (ft_strncmp((char *)tmp->content, str, plus_index) == 0
			&& !((char *)tmp->content)[plus_index])
		{
			tmp_content = tmp->content;
			tmp->content = ft_strjoin(tmp->content, str + plus_index + 1);
			free(tmp_content);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	replace_or_join(char *str, int plus_index)
{
	if (var_was_replace_or_join(str, plus_index))
		return ;
	str = replace_word(str, plus_index, 1, "");
	ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(str)));
	return ;
}

int	replace_env_var_if_exist2(char *str, t_list *tmp)
{
	int	len;
	int	env_var_len;

	len = ft_strlen(str);
	if (ft_strncmp(tmp->content, str, len) == 0
		&& ((char *)tmp->content)[len] == '=')
		return (1);
	else
	{
		env_var_len = ft_strlen(tmp->content);
		if (ft_strncmp((char *)tmp->content, str, env_var_len) == 0
			&& str[env_var_len] == '=')
		{
			free(tmp->content);
			tmp->content = ft_strdup(str);
			return (1);
		}
	}
	return (0);
}

int	replace_env_var_if_exist(char *str)
{
	t_list	*tmp;

	tmp = g_env;
	while (tmp)
	{
		if (ft_strcmp(str, "_") == 0 || ft_strncmp(str, "_=", 2) == 0)
			return (1);
		else if (ft_strcmp_char(tmp->content, str, '=') == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(str);
			return (1);
		}
		else
		{
			if (replace_env_var_if_exist2(str, tmp))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
