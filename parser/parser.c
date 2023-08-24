/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:34:59 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 15:15:13 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static t_redirec_type	convert_to_redirection(t_type type)
{
	if (type == TOKEN_REDIRECT_OUTPUT)
		return (REDIRECTION_OUTPUT);
	else if (type == TOKEN_REDIRECT_INPUT)
		return (REDIRECTION_INPUT);
	else if (type == TOKEN_REDIRECT_APPEND)
		return (REDIRECTION_APPEND);
	else
		return (REDIRECTION_HEREDOC);
}

static t_cmd_file	set_error(t_cmd_file *cmd_file, t_token token)
{
	free(cmd_file->error);
	cmd_file->error = ft_strjoin(
			"bash: syntax error near unexpected token ",
			(char *[]){"'<'", "'>'", "'>>'", "'<<'", "'|'", "'newline'", "",
			""}[token.type]);
	if (token.type == TOKEN_ERROR)
	{
		free(cmd_file->error);
		cmd_file->error = ft_strdup(token.value);
	}
	return (*cmd_file);
}

t_redirection	*make_redirect(t_cmd_file *cmd_file, t_token *token,
		const char **str)
{
	t_redirection	*redirection;

	redirection = ft_calloc(1, sizeof(t_redirection));
	redirection->redic_type = convert_to_redirection(token->type);
	ft_lstadd_back(&cmd_file->redirection, ft_lstnew(redirection));
	*token = get_next_token(str);
	return (redirection);
}

void	set_error_msg(t_cmd_file *cmd_file, t_token *token, const char **str)
{
	if (token->type == TOKEN_PIPE && !(**str))
		cmd_file->error = ft_strdup("bash: syntax error: "
				"unexpected end of file");
	if (token->type == TOKEN_ERROR)
	{
		free(cmd_file->error);
		cmd_file->error = ft_strdup(token->value);
	}
}

t_cmd_file	get_cmd(const char **str)
{
	t_cmd_file		cmd_file;
	t_token			token;
	t_redirection	*redirection;

	ft_memset(&cmd_file, 0, sizeof(t_cmd_file));
	token = get_next_token(str);
	if (token.type == TOKEN_PIPE)
		return (set_error(&cmd_file, token));
	while (is_spicial(token.type))
	{
		if (is_redirection(token.type))
		{
			redirection = make_redirect(&cmd_file, &token, str);
			if (token.type != TOKEN_WORD)
				return (set_error(&cmd_file, token));
			redirection->file_name = token.value;
		}
		else
			ft_lstadd_back(&cmd_file.cmds, ft_lstnew(token.value));
		token = get_next_token(str);
	}
	set_error_msg(&cmd_file, &token, str);
	return (cmd_file);
}
