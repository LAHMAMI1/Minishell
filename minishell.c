/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:39:06 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/21 16:12:32 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/parser.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

t_list	*g_env;

int	exit_by_signal(t_list *list)
{
	t_list		*tmp;
	t_cmd_file	*cmd_fil;

	tmp = list;
	while (tmp)
	{
		cmd_fil = (t_cmd_file *)tmp->content;
		if (cmd_fil->exit_by_signal == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	line_isspaces(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

void	parse_execu(const char *input)
{
	t_list		*list;
	t_execution	*executor;

	list = global_parser(input);
	executor = ft_calloc(sizeof(t_execution), 1);
	if (list && !exit_by_signal(list))
		global_executor(list, executor);
	ft_lstclear(&list, &free_t_cmd_file);
	free(executor);
}

int	main(int ac, char **av, const char **env)
{
	const char	*input;
	int			exit_status;

	(void)ac;
	(void)av;
	g_env = get_env_variables(env);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell>");
		if (!input && printf("exit\n"))
			break ;
		add_history(input);
		if (!line_isspaces(input))
			parse_execu(input);
		free((char *)input);
	}
	exit_status = ft_atoi(get_env_var_value("?"));
	ft_lstclear(&g_env, free);
	return (exit_status);
}
