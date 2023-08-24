/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:50:37 by olahmami          #+#    #+#             */
/*   Updated: 2023/08/21 16:17:20 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_all_cmd(t_execution *executor, int *status, t_list *tmp,
		t_list *list)
{
	while (executor->i < executor->size_cmds && list)
	{
		executor->cmd_file = (t_cmd_file *)list->content;
		executor->in_out_fd = executor->cmd_file->in_out_fd;
		executor->cmds = (t_list *)executor->cmd_file->cmds;
		if (executor->cmd_file->pipe_has_error == 1 || !executor->cmds)
		{
			executor->i++;
			list = list->next;
			continue ;
		}
		executor->flag = 0;
		if (executor->i == executor->size_cmds - 1)
			fd_out(executor);
		else
			open_pipe(executor);
		dup_after_pipe(executor);
		fork_process(executor, status, tmp);
		list = list->next;
		executor->i++;
	}
}

void	child_execute(t_execution *executor, int *status)
{
	if (check_builtin(*executor->cmd_file) == 1)
	{
		*status = builtin(*executor->cmd_file, &executor->flag);
		update_exit_status_var(WTERMSIG(*status));
		exit(*status);
	}
	else if (executor->flag == 0)
	{
		close_if_not(executor->fdin, 0);
		executor->executable = NULL;
		executor->split_cmds
			= convert_linkedlist_to_char_arr_cmd(executor->cmds);
		executor->env = convert_linkedlist_to_char_arr();
		executor->split_env = read_env(executor->env,
				executor->split_cmds);
		executor->executable = cmd_extand(
				executor->split_env, executor->executable,
				executor->split_cmds);
		execution(executor->env, executor->executable, executor->split_cmds);
	}
}

void	save_and_close(t_execution *executor)
{
	dup2(executor->tmp_in, 0);
	dup2(executor->tmp_out, 1);
	close_if_not(executor->tmp_in, 0);
	close_if_not(executor->tmp_out, 1);
	close_if_not(executor->fdin, 0);
}

void	waiting(t_execution *executor, int *status)
{
	int	i;

	if (waitpid(executor->pid, status, 0) == -1)
		return ;
	i = 0;
	while (++i < executor->size_cmds)
		wait(NULL);
	if (WIFEXITED(*status))
		update_exit_status_var(WEXITSTATUS(*status));
	else
	{
		if (WTERMSIG(*status) == 3)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (WTERMSIG(*status) == 2)
			ft_putstr_fd("\n", 1);
		update_exit_status_var(WTERMSIG(*status) + 128);
	}
}
