/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:12:22 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/18 17:15:52 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

void	print_args(void *content)
{
	printf("[%s] \n", (char *)content);
}

static void	print_redirections(void *content)
{
	t_redirection	*redirection;

	redirection = content;
	printf(" -->  [%s] => %s\n",
		(char *[]){"<", ">", ">>", "<<"}[redirection->redic_type],
		redirection->file_name);
}

void	print_cmd(t_cmd_file cmd_file)
{
	if (cmd_file.error)
	{
		printf("%s\n", cmd_file.error);
		return ;
	}
	ft_lstiter(cmd_file.cmds, &print_args);
	printf("\n");
	ft_lstiter(cmd_file.redirection, &print_redirections);
	printf("infile fd  --> [%d]\n", cmd_file.in_out_fd.in_fd);
	printf("outfile fd --> [%d]\n", cmd_file.in_out_fd.out_fd);
	printf("pipe_has_error --> [%d]\n\n", cmd_file.pipe_has_error);
}

int	compair_arr_strings(const char **arr_1, const char **arr_2)
{
	int	i;

	i = 0;
	while (arr_1[i] != NULL && arr_2[i] != NULL)
	{
		if (ft_strlen(arr_1[i]) != ft_strlen(arr_2[i]))
			return (-1);
		if (ft_strncmp(arr_1[i], arr_2[i], ft_strlen(arr_1[i])) != 0)
			return (-1);
		i++;
	}
	if (arr_1[i] || arr_2[i])
		return (-1);
	return (0);
}
