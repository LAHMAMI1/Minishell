/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_expand_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:22:50 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/21 11:46:39 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*replace_word(const char *str, int index, int size,
		const char *replacement)
{
	int		str_len;
	int		replace_len;
	int		new_size;
	char	*new_str;

	str_len = ft_strlen(str);
	replace_len = ft_strlen(replacement);
	new_size = str_len - size + replace_len;
	new_str = malloc(sizeof(char) * (new_size + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, index + 1);
	ft_strlcpy(new_str + index, replacement, replace_len + 1);
	ft_strlcpy(new_str + (index + replace_len), str + (index + size), str_len
		- index - size + 1);
	return (new_str);
}

char	*remove_single_quotes(char *str, int *i_ptr, int *has_quote)
{
	int		j;
	int		i;
	char	*var;
	char	*tmp;

	i = *i_ptr;
	j = i + 1;
	*has_quote = 1;
	while (str[j] && str[j] != str[i])
		j++;
	var = malloc(sizeof(char) * (j - i));
	ft_strlcpy(var, str + i + 1, j - i);
	tmp = replace_word(str, i, j - i + 1, var);
	*i_ptr += ft_strlen(var);
	free(var);
	free(str);
	return (tmp);
}

char	*expand_double_quotes(char *var)
{
	int			i;
	char		*var_name;
	const char	*var_value;
	char		*tmp;

	i = 0;
	while (var[i])
	{
		if (var[i] == '$' && var[i + 1])
		{
			var_name = extract_name(var + i);
			if (!var_name && i++)
				continue ;
			var_value = get_var_value(var_name);
			tmp = var;
			var = replace_word(var, i, ft_strlen(var_name) + 1, var_value);
			free(tmp);
			i += ft_strlen(var_value);
			free(var_name);
		}
		else
			i++;
	}
	return (var);
}

char	*remove_double_quotes(char *str, int *i_ptr, int to_be_expand,
		int *has_quote)
{
	int		j;
	int		i;
	char	*var;
	char	*tmp;

	i = *i_ptr;
	j = i + 1;
	while (str[j] && str[j] != str[i])
		j++;
	var = malloc(sizeof(char) * (j - i));
	ft_strlcpy(var, str + i + 1, j - i);
	if (to_be_expand)
		var = expand_double_quotes(var);
	tmp = replace_word(str, i, j - i + 1, var);
	*i_ptr += ft_strlen(var);
	free(var);
	free(str);
	*has_quote = 1;
	return (tmp);
}
