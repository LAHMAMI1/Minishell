/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:47:52 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/18 17:50:57 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_special(char c)
{
	return (c == ' ' || c == '>' || c == '<' || c == '|');
}

int	find_closing_qq(const char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != str[0])
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i + 1);
}

t_token	get_word(const char **str)
{
	t_token	token;
	size_t	i;
	int		len;

	i = 0;
	while ((*str)[i] && !is_special((*str)[i]))
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			len = find_closing_qq(*str + i);
			if (len == -1)
				return ((t_token){.value = (char *)"unexpeceted EOF while "
					"looking for closing quote", .type = TOKEN_ERROR});
			else
				i += len;
		}
		else
			i++;
	}
	token.type = TOKEN_WORD;
	token.value = (char *)malloc(sizeof(char) * (i + 1));
	ft_strlcpy(token.value, *str, i + 1);
	*str += i;
	return (token);
}
