/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:29:44 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 12:35:45 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*expand_heredoc_del(char *str, int *hd_has_quotes)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			*hd_has_quotes = 1;
			str = remove_double_quotes(str, &i, 0, hd_has_quotes);
		}
		else if (str[i] == '\'')
		{
			*hd_has_quotes = 1;
			str = remove_single_quotes(str, &i, hd_has_quotes);
		}
		else
			i++;
	}
	return (str);
}

int	file_expander(t_list *list, int *hd_has_quotes)
{
	char	*file_name;
	t_list	*new_list;
	char	*file_name_befor;

	new_list = NULL;
	if (!((t_redirection *)list->content)->file_name)
		return (0);
	if (((t_redirection *)list->content)->redic_type == REDIRECTION_HEREDOC)
	{
		((t_redirection *)list->content)->file_name = expand_heredoc_del(
				((t_redirection *)list->content)->file_name, hd_has_quotes);
		return (1);
	}
	file_name = ft_strdup(((t_redirection *)list->content)->file_name);
	file_name_befor = ft_strdup(((t_redirection *)list->content)->file_name);
	file_name = do_ifs_expander(&new_list, file_name);
	if (ft_lstsize(new_list) != 1 && printf("%s: ambiguous redirect\n",
			file_name_befor))
		return (free(file_name_befor), free(file_name), ft_lstclear(&new_list,
				free), 0);
	free(file_name_befor);
	free(file_name);
	free(((t_redirection *)list->content)->file_name);
	((t_redirection *)list->content)->file_name = (char *)new_list->content;
	return (ft_lstclear(&new_list, NULL), 1);
}
