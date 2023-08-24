/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:14:45 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/18 11:19:02 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

void	print_env_error(char *str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int	ft_env(t_list *list)
{
	t_list	*env_tmp;

	env_tmp = g_env;
	if (ft_lstsize(list) > 1)
	{
		print_env_error((char *)list->next->content);
		return (127);
	}
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->content, "?=", 2) == 0)
		{
			env_tmp = env_tmp->next;
			continue ;
		}
		if (!ft_strchr(env_tmp->content, '='))
		{
			env_tmp = env_tmp->next;
			continue ;
		}
		printf("%s\n", (char *)env_tmp->content);
		env_tmp = env_tmp->next;
	}
	return (SUCCESS);
}
