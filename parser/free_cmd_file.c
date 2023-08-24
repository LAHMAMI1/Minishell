/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 00:50:57 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 00:55:38 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	free_redir(void *ptr)
{
	t_redirection	*redir;

	redir = (t_redirection *)ptr;
	free(redir->file_name);
	free(redir);
}

void	free_t_cmd_file(void *arg)
{
	t_cmd_file	*cmd;

	cmd = (t_cmd_file *)arg;
	ft_lstclear(&cmd->cmds, free);
	ft_lstclear(&cmd->redirection, free_redir);
	free(cmd->error);
	free(cmd);
}
