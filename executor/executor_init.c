/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:05:47 by olahmami          #+#    #+#             */
/*   Updated: 2023/08/21 17:50:27 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fd_in(t_execution *executor)
{
	if (executor->in_out_fd.in_fd > 0)
		executor->fdin = executor->in_out_fd.in_fd;
	else
		executor->fdin = dup(executor->tmp_in);
}

void	fd_out(t_execution *executor)
{
	if (executor->in_out_fd.out_fd > 1)
		executor->fdout = executor->in_out_fd.out_fd;
	else
		executor->fdout = dup(executor->tmp_out);
}

void	execute_one_builtin(t_execution *executor, int *status)
{
	if (executor->size_cmds == 1 && check_builtin(*executor->cmd_file) == 1)
	{
		fd_out(executor);
		dup2(executor->fdout, 1);
		close(executor->fdout);
		if (!executor->cmd_file->pipe_has_error)
			*status = builtin(*executor->cmd_file, &executor->flag);
		else
		{
			*status = 1;
			executor->flag = 1;
		}
		update_exit_status_var(*status);
		executor->i = 1;
	}
}

void	init_execution(t_execution *executor, t_list *list, int *status)
{
	executor->cmd_file = (t_cmd_file *)list->content;
	executor->in_out_fd = executor->cmd_file->in_out_fd;
	executor->size_cmds = ft_lstsize(list);
	executor->tmp_in = dup(0);
	executor->tmp_out = dup(1);
	executor->fdin = 0;
	fd_in(executor);
	execute_one_builtin(executor, status);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

char	**ft_split_exec(char const *s, char c)
{
	unsigned int	h;
	unsigned int	w;
	int				i;
	char			**new_array;

	h = -1;
	w = 0;
	if (!s)
		return (NULL);
	new_array = malloc((ft_counter(s, c) + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = -1;
	while (++h <= ft_strlen(s))
	{
		if (s[h] != c && i < 0)
			i = h;
		else if ((s[h] == c || h == ft_strlen(s)) && i >= 0)
		{
			new_array[w++] = ft_dup((s + i), (h - i));
			i = -2;
		}
	}
	new_array[w] = 0;
	return (new_array);
}
