/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:37:04 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/21 16:04:17 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	func(char *str, int *i, char *(func1)(char *, int *), char *(func2)(char *,
			int *, int))
{
	if (str[*i] == '\'')
		func1(str, i);
	if (str[*i] == '\"')
		func2(str, i, 1);
	return (1);
}

static char	*do_ifs_expander_norm(t_list **new_list, char *word,
		t_ifs_exp *ifs_exp)
{
	while (word[ifs_exp->i])
	{
		if (word[ifs_exp->i] == '$' && word[ifs_exp->i + 1])
		{
			ifs_exp->var_name = extract_name(word + ifs_exp->i);
			if (!ifs_exp->var_name && ++ifs_exp->i)
				continue ;
			ifs_exp->str = concat_leftouvers(ifs_exp->str, word, ifs_exp->i,
					ifs_exp->j);
			ifs_exp->str = word_split_to_node(new_list,
					get_var_value(ifs_exp->var_name), ifs_exp->str,
					&ifs_exp->has_quote);
			ifs_exp->i += ft_strlen(ifs_exp->var_name) + 1;
			free(ifs_exp->var_name);
			ifs_exp->j = ifs_exp->i;
		}
		else if (word[ifs_exp->i] == '\'')
			word = remove_single_quotes(word, &ifs_exp->i, &ifs_exp->has_quote);
		else if (word[ifs_exp->i] == '"')
			word = remove_double_quotes(word, &ifs_exp->i, 1,
					&ifs_exp->has_quote);
		else
			ifs_exp->i++;
	}
	return (word);
}

char	*do_ifs_expander(t_list **new_list, char *word)
{
	t_ifs_exp	*ifs_exp;

	ifs_exp = ft_calloc(sizeof(t_ifs_exp), 1);
	ifs_exp->has_quote = 0;
	ifs_exp->i = 0;
	ifs_exp->j = ifs_exp->i;
	ifs_exp->str = ft_strdup("");
	word = do_ifs_expander_norm(new_list, word, ifs_exp);
	ifs_exp->str = concat_leftouvers(ifs_exp->str, word, ifs_exp->i,
			ifs_exp->j);
	push_if_not_empty(new_list, ifs_exp->str, &ifs_exp->has_quote);
	free(ifs_exp);
	return (word);
}

void	ifs_expander(t_list *list, char *ifs)
{
	t_list	*new_list;
	char	*word;

	(void)ifs;
	new_list = NULL;
	word = (char *)list->content;
	list->content = do_ifs_expander(&new_list, word);
	expande_node(list, new_list);
}
