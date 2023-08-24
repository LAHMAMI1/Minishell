/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:42:07 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/18 17:08:44 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	var_sould_be_remove(char *node_content, char *to_be_remove)
{
	int	to_be_remove_len;

	to_be_remove_len = ft_strlen(to_be_remove);
	if (ft_strcmp(node_content, to_be_remove) == 0)
		return (1);
	else if (ft_strncmp(node_content, to_be_remove, to_be_remove_len) == 0
		&& node_content[to_be_remove_len] == '=')
		return (1);
	return (0);
}

void	remove_node_must_be_remove(t_list **list, char *to_be_remove)
{
	t_list	*current;
	t_list	*previous;

	current = *list;
	previous = NULL;
	while (current != NULL)
	{
		if (var_sould_be_remove((char *)current->content, to_be_remove) == 1)
		{
			if (previous == NULL)
				*list = current->next;
			else
				previous->next = current->next;
			free(current->content);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	remove_node_from_list(t_list **list, char *to_be_remove)
{
	if (list == NULL || *list == NULL || to_be_remove == NULL)
	{
		return ;
	}
	if (ft_strcmp(to_be_remove, "_") == 0 || ft_strncmp(to_be_remove, "_=",
			2) == 0)
		return ;
	if (ft_strcmp(to_be_remove, "?") == 0 || ft_strncmp(to_be_remove, "?=",
			2) == 0)
		return ;
	remove_node_must_be_remove(list, to_be_remove);
}

int	ft_unset(t_list *list_cmd)
{
	t_list	*tmp_list_cmd;
	int		to_be_returnd;

	to_be_returnd = SUCCESS;
	tmp_list_cmd = list_cmd;
	if (ft_lstsize(tmp_list_cmd) == 1)
		return (to_be_returnd);
	while (tmp_list_cmd)
	{
		if (is_unvalid_name(tmp_list_cmd->content) == 1)
		{
			ft_putstr_fd("bash: unset: '", 2);
			ft_putstr_fd((char *)tmp_list_cmd->content, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			tmp_list_cmd = tmp_list_cmd->next;
			continue ;
			to_be_returnd = ERROR;
		}
		remove_node_from_list(&g_env, tmp_list_cmd->content);
		tmp_list_cmd = tmp_list_cmd->next;
	}
	return (to_be_returnd);
}
