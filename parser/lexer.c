/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:31:17 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/19 11:46:22 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_token	handle_input_herdoc(const char **str)
{
	(*str)++;
	if (**str == '<')
	{
		(*str)++;
		return ((t_token){.value = NULL, .type = TOKEN_HEREDOC});
	}
	return ((t_token){.value = NULL, .type = TOKEN_REDIRECT_INPUT});
}

static t_token	handle_output_append(const char **str)
{
	(*str)++;
	if (**str == '>')
	{
		(*str)++;
		return ((t_token){.value = NULL, .type = TOKEN_REDIRECT_APPEND});
	}
	return ((t_token){.value = NULL, .type = TOKEN_REDIRECT_OUTPUT});
}

t_token	get_next_token(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '|')
	{
		(*str)++;
		return ((t_token){.value = NULL, .type = TOKEN_PIPE});
	}
	else if (**str == '>')
		return (handle_output_append(str));
	else if (**str == '<')
		return (handle_input_herdoc(str));
	else if (**str != '\0')
		return (get_word(str));
	else
		return ((t_token){.value = NULL, .type = TOKEN_END});
}
