/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:37:51 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 15:13:42 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void	print_sorted_env(void)
{
	char	**env_arr;
	int		size;
	int		i;

	i = -1;
	size = ft_lstsize(g_env);
	env_arr = convert_linkedlist_to_char_arr();
	sort_env(env_arr, size);
	while (++i < size)
	{
		if (ft_strncmp(env_arr[i], "?=", 2) == 0)
			continue ;
		print_var(env_arr[i]);
	}
	free(env_arr);
}

int	replace_or_join_if_exist(t_list *tmp)
{
	int	plus_is_exist;

	plus_is_exist = 0;
	plus_is_exist = should_be_join(tmp->content);
	if (plus_is_exist)
	{
		replace_or_join(tmp->content, plus_is_exist);
		return (1);
	}
	if (replace_env_var_if_exist(tmp->content))
	{
		return (1);
	}
	return (0);
}

void	print_export_error(char *str)
{
	ft_putstr_fd("bash: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	export_all_argument(t_list *list, int *return_value)
{
	t_list	*tmp;

	tmp = list;
	tmp = tmp->next;
	while (tmp)
	{
		if (is_unvalid_name(tmp->content) == 1
			|| is_unvalid_var_name(tmp->content) == 1)
		{
			print_export_error((char *)tmp->content);
			tmp = tmp->next;
			*return_value = ERROR;
			continue ;
		}
		if (replace_or_join_if_exist(tmp))
		{
			tmp = tmp->next;
			continue ;
		}
		ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(tmp->content)));
		tmp = tmp->next;
	}
}

int	ft_export(t_list *list)
{
	int	return_value;

	return_value = SUCCESS;
	if (ft_lstsize(list) == 1)
	{
		print_sorted_env();
		return (return_value);
	}
	else
		export_all_argument(list, &return_value);
	return (return_value);
}
