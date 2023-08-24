/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:20:13 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/18 11:20:19 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	must_be_skiped(char *str)
{
	int	i;

	if (ft_strcmp(str, "-n") == 0)
		return (0);
	else if (ft_strncmp(str, "-n", 2) == 0)
	{
		i = 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

int	ft_echo(t_list *list)
{
	t_list	*tmp;
	int		print_new_line;
	int		to_be_returned;

	to_be_returned = SUCCESS;
	tmp = list;
	print_new_line = 1;
	tmp = tmp->next;
	while (tmp)
	{
		if (must_be_skiped(tmp->content) == 1)
			break ;
		print_new_line = 0;
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_putstr_fd((char *)tmp->content, STDOUT_FILENO);
		if (tmp->next)
			ft_putstr_fd(" ", STDOUT_FILENO);
		tmp = tmp->next;
	}
	if (print_new_line == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (to_be_returned);
}
