/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_to_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:13:00 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 12:36:26 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	node_maker(t_list **new_list, char **str, int *has_quote)
{
	push_if_not_empty(new_list, *str, has_quote);
	*str = ft_strdup("");
}

void	word_not_empty(t_list **new_list, char **word_splited, char **str,
		int *has_quote)
{
	char	*tmp;
	int		k;

	tmp = *str;
	*str = ft_strjoin(*str, *word_splited);
	free(tmp);
	k = 0;
	while (word_splited[k + 1])
	{
		push_if_not_empty(new_list, *str, has_quote);
		*str = ft_strdup(word_splited[k + 1]);
		k++;
	}
}

char	*word_split_to_node(t_list **new_list, const char *var_value, char *str,
		int *has_quote)
{
	char		**word_splited;
	const char	*ifs;

	ifs = get_env_var_value("IFS");
	if (!ifs)
		ifs = " ";
	word_splited = field_splitting(var_value, (char *)ifs);
	if (start_with_only_whitspace(var_value, (char *)ifs))
		node_maker(new_list, &str, has_quote);
	if (*word_splited)
		word_not_empty(new_list, word_splited, &str, has_quote);
	if (end_with_only_whitspace(var_value, (char *)ifs))
		node_maker(new_list, &str, has_quote);
	ft_free_split(word_splited);
	return (str);
}

char	*extract_name(char *var)
{
	int		i;
	int		j;
	char	*var_name;

	i = 0;
	if (var[0] != '$')
		return (NULL);
	i++;
	if (var[i] == '?')
		return (ft_strdup("?"));
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (NULL);
	j = i;
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	var_name = malloc(sizeof(char) * (i - j + 1));
	if (!var_name)
		return (NULL);
	ft_memcpy(var_name, var + j, (i - j));
	var_name[i - j] = 0;
	return (var_name);
}
