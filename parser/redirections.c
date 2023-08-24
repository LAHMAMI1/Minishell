/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:36:11 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/21 16:14:28 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*expand_heredoc_vars(char *var)
{
	int			i;
	char		*var_name;
	char		*tmp;
	const char	*var_value;

	i = 0;
	while (var[i])
	{
		if (var[i] == '$' && var[i + 1])
		{
			var_name = extract_name(var + i);
			if (!var_name && i++)
				continue ;
			var_value = get_env_var_value(var_name);
			if (!var_value)
				var_value = "";
			tmp = var;
			var = replace_word(var, i, ft_strlen(var_name) + 1, var_value);
			i += ft_strlen(var_value);
			(free(tmp), free(var_name));
		}
		else
			i++;
	}
	return (var);
}

static void	child_here_doc(int fildes[2], t_redirection *redirection,
		int hd_has_quotes)
{
	char	*input;

	signal(SIGINT, herd_sig);
	close_if_not(fildes[0], STDIN_FILENO);
	input = readline(">");
	while (input && ft_strcmp(redirection->file_name, input) != 0)
	{
		if (!hd_has_quotes)
			input = expand_heredoc_vars(input);
		ft_putendl_fd(input, fildes[1]);
		free(input);
		input = readline(">");
	}
	if (!input)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(EOF_ERROR, 2);
		ft_putstr_fd(redirection->file_name, 2);
		ft_putendl_fd("')", 2);
	}
	free(input);
	exit(0);
}

static void	waiting_here_doc(pid_t pid, t_cmd_file *cmd_file, int fildes[2])
{
	int	status;

	waitpid(pid, &status, 0);
	if (status == 256)
	{
		update_exit_status_var(130);
		cmd_file->exit_by_signal = 1;
	}
	close_if_not(fildes[1], STDOUT_FILENO);
}

int	open_here_doc(t_cmd_file *cmd_file, int hd_has_quotes)
{
	t_redirection	*redirection;
	t_list			*tmp;
	int				fildes[2];
	pid_t			pid;

	fildes[0] = STDIN_FILENO;
	tmp = cmd_file->redirection;
	while (tmp && !cmd_file->exit_by_signal)
	{
		redirection = (t_redirection *)tmp->content;
		if (redirection->redic_type == REDIRECTION_HEREDOC)
		{
			pipe(fildes);
			pid = fork();
			signal(SIGINT, SIG_IGN);
			if (pid == -1)
				exit(1);
			else if (pid == 0)
				child_here_doc(fildes, redirection, hd_has_quotes);
			else
				waiting_here_doc(pid, cmd_file, fildes);
		}
		tmp = tmp->next;
	}
	return (fildes[0]);
}

int	last_in_file(t_cmd_file *cmd_file)
{
	t_list			*tmp;
	t_redirection	*redirection;
	int				last_in_file;

	last_in_file = REDIRECTION_INPUT;
	tmp = cmd_file->redirection;
	while (tmp)
	{
		redirection = (t_redirection *)tmp->content;
		if (redirection->redic_type == REDIRECTION_INPUT)
			last_in_file = REDIRECTION_INPUT;
		else if (redirection->redic_type == REDIRECTION_HEREDOC)
			last_in_file = REDIRECTION_HEREDOC;
		tmp = tmp->next;
	}
	return (last_in_file);
}
