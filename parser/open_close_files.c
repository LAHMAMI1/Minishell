/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:51:42 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/19 17:54:36 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	redirect_in(t_cmd_file *cmd_file, char *filename)
{
	close_if_not(cmd_file->in_out_fd.in_fd, STDIN_FILENO);
	cmd_file->in_out_fd.in_fd = open(filename, O_RDONLY);
	if (cmd_file->in_out_fd.in_fd == -1)
	{
		cmd_file->pipe_has_error = 1;
		perror(filename);
	}
}

void	redirect_out(t_cmd_file *cmd_file, char *filename)
{
	close_if_not(cmd_file->in_out_fd.out_fd, STDOUT_FILENO);
	cmd_file->in_out_fd.out_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT,
			0644);
	if (cmd_file->in_out_fd.in_fd == -1)
	{
		cmd_file->pipe_has_error = 1;
		perror(filename);
	}
}

void	redirect_append(t_cmd_file *cmd_file, char *filename)
{
	close_if_not(cmd_file->in_out_fd.out_fd, STDOUT_FILENO);
	cmd_file->in_out_fd.out_fd = open(filename,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd_file->in_out_fd.in_fd == -1)
	{
		cmd_file->pipe_has_error = 1;
		perror(filename);
	}
}

void	redirect_herdoc(t_cmd_file *cmd_file, int here_doc_fd)
{
	close_if_not(cmd_file->in_out_fd.in_fd, STDIN_FILENO);
	cmd_file->in_out_fd.in_fd = here_doc_fd;
}

void	extract_in_out_fd(t_cmd_file *cmd_file, int hd_has_quotes)
{
	t_list			*tmp;
	t_redirection	*redirection;
	int				here_doc_fd;

	tmp = cmd_file->redirection;
	cmd_file->in_out_fd.in_fd = STDIN_FILENO;
	cmd_file->in_out_fd.out_fd = STDOUT_FILENO;
	here_doc_fd = open_here_doc(cmd_file, hd_has_quotes);
	cmd_file->pipe_has_error = 0;
	while (tmp && !(cmd_file->pipe_has_error))
	{
		redirection = (t_redirection *)tmp->content;
		if (redirection->redic_type == REDIRECTION_INPUT)
			redirect_in(cmd_file, redirection->file_name);
		if (redirection->redic_type == REDIRECTION_OUTPUT)
			redirect_out(cmd_file, redirection->file_name);
		if (redirection->redic_type == REDIRECTION_APPEND)
			redirect_append(cmd_file, redirection->file_name);
		tmp = tmp->next;
	}
	if (last_in_file(cmd_file) == REDIRECTION_HEREDOC)
		redirect_herdoc(cmd_file, here_doc_fd);
	else
		close_if_not(here_doc_fd, STDIN_FILENO);
}
