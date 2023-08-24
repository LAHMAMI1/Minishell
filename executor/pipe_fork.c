/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:06:44 by olahmami          #+#    #+#             */
/*   Updated: 2023/08/21 11:20:43 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_pipe(t_execution *executor)
{
	if (pipe(executor->fd) == -1)
		exit(1);
	if (executor->in_out_fd.out_fd > 1)
	{
		executor->fdout = executor->in_out_fd.out_fd;
		executor->outfile = executor->fd[1];
		dup2(executor->outfile, 1);
		close_if_not(executor->outfile, 1);
	}
	else
		executor->fdout = executor->fd[1];
}

void	dup_after_pipe(t_execution *executor)
{
	if (executor->fdin != executor->in_out_fd.in_fd)
	{
		if (executor->in_out_fd.in_fd > 0)
		{
			close_if_not(executor->fdin, 0);
			executor->fdin = executor->in_out_fd.in_fd;
		}
	}
	dup2(executor->fdin, 0);
	close_if_not(executor->fdin, 0);
	executor->fdin = executor->fd[0];
	dup2(executor->fdout, 1);
	close_if_not(executor->fdout, 1);
}

void	fork_process(t_execution *executor, int *status, t_list *tmp)
{
	executor->pid = fork();
	if (executor->pid == -1)
		(perror("fork"), exit(1));
	else if (executor->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (tmp)
		{
			if (executor->cmd_file->exit_by_signal == 1)
				exit(130);
			tmp = tmp->next;
		}
		child_execute(executor, status);
		exit(*status);
	}
}
