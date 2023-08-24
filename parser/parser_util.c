/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:32:29 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 16:23:02 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	remove_null_values(t_list **list_ptr)
{
	t_list_pt	list_pt;

	list_pt.list = *list_ptr;
	list_pt.current = list_pt.list;
	list_pt.previous = NULL;
	while (list_pt.current)
	{
		if (list_pt.current->content == NULL)
		{
			list_pt.nextnode = list_pt.current->next;
			if (list_pt.previous)
				list_pt.previous->next = list_pt.nextnode;
			else
				list_pt.list = list_pt.nextnode;
			free(list_pt.current->content);
			free(list_pt.current);
			list_pt.current = list_pt.nextnode;
		}
		else
		{
			list_pt.previous = list_pt.current;
			list_pt.current = list_pt.current->next;
		}
	}
	*list_ptr = list_pt.list;
}

int	expand_cmd_list(t_cmd_file *cmd_file, char *ifs)
{
	t_list	*tmp;
	t_list	*files;
	int		hd_has_quotes;

	hd_has_quotes = 0;
	tmp = cmd_file->cmds;
	files = cmd_file->redirection;
	while (tmp)
	{
		ifs_expander(tmp, ifs);
		tmp = tmp->next;
	}
	while (files)
	{
		if (!file_expander(files, &hd_has_quotes))
		{
			cmd_file->pipe_has_error = 1;
			return (0);
		}
		files = files->next;
	}
	extract_in_out_fd(cmd_file, hd_has_quotes);
	remove_null_values(&cmd_file->cmds);
	return (1);
}

void	maximum_here_doc_count(t_cmd_file *cmd_file)
{
	t_list			*redirection;
	t_redirection	*file_type;
	int				counter;

	counter = 0;
	redirection = cmd_file->redirection;
	while (redirection)
	{
		file_type = (t_redirection *)(redirection->content);
		if (file_type->redic_type == REDIRECTION_HEREDOC)
			counter++;
		redirection = redirection->next;
	}
	if (counter > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		exit(2);
	}
}

void	check_error_herdoc(t_cmd_file *cmd_file, t_list *list)
{
	printf("%s\n", cmd_file->error);
	update_exit_status_var(2);
	free_t_cmd_file(cmd_file);
	ft_lstclear(&list, &free_t_cmd_file);
}

t_list	*global_parser(const char *str)
{
	t_list		*list;
	t_cmd_file	*cmd_file;
	int			exit_signal;
	const char	*ifs;

	list = NULL;
	exit_signal = 0;
	ifs = get_env_var_value("IFS");
	if (!ifs)
		ifs = " ";
	while (*str && !exit_signal)
	{
		cmd_file = malloc(sizeof(t_cmd_file));
		*cmd_file = get_cmd(&str);
		if (cmd_file->error)
		{
			check_error_herdoc(cmd_file, list);
			return (NULL);
		}
		maximum_here_doc_count(cmd_file);
		ft_lstadd_back(&list, ft_lstnew(cmd_file));
		expand_cmd_list(cmd_file, (char *)ifs);
		exit_signal = cmd_file->exit_by_signal;
	}
	return (list);
}
