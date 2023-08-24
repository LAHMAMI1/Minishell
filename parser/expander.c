/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:42:06 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/19 13:19:34 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

const char	*get_env_var_value(const char *var)
{
	int		len;
	t_list	*tmp;

	len = ft_strlen(var);
	tmp = g_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, var, len) == 0
			&& ((char *)tmp->content)[len] == '=')
			return ((char *)tmp->content + len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

void	expande_node(t_list *list, t_list *new_list)
{
	t_list	*tmp;

	free(list->content);
	if (!new_list)
	{
		list->content = NULL;
		return ;
	}
	list->content = new_list->content;
	tmp = new_list->next;
	free(new_list);
	if (tmp == NULL)
		return ;
	new_list = tmp;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = list->next;
	list->next = new_list;
}

char	*concat_leftouvers(char *str, char *word, int i, int j)
{
	char	*prev;
	char	*tmp;

	prev = ft_substr(word, j, i - j);
	tmp = str;
	str = ft_strjoin(str, prev);
	free(prev);
	free(tmp);
	return (str);
}

void	push_if_not_empty(t_list **new_list, char *str, int *has_quote)
{
	if (!*has_quote && str[0] == '\0')
		return (free(str));
	*has_quote = 0;
	ft_lstadd_back(new_list, ft_lstnew(str));
}

const char	*get_var_value(char *var_name)
{
	const char	*var_value;

	var_value = get_env_var_value(var_name);
	if (!var_value)
		var_value = "";
	return (var_value);
}
