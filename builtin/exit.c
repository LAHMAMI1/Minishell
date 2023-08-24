/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:27:59 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/21 17:13:41 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void	exit_without_args(void)
{
	long	exit_status;

	exit_status = 0;
	exit_status = ft_atoi(get_env_var_value("?"));
	ft_putstr_fd("exit\n", 2);
	exit(exit_status);
}

void	print_exit_error(char *str)
{
	ft_putstr_fd("exit\nbash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" numeric argument required\n", 2);
	exit(2);
}

int	ft_exit(t_list *list)
{
	t_list	*tmp_list;
	long	exit_status;

	exit_status = 0;
	tmp_list = list;
	tmp_list = tmp_list->next;
	if (ft_lstsize(list) == 1)
		exit_without_args();
	if (!ft_isnumber(tmp_list->content))
		print_exit_error((char *)tmp_list->content);
	if (ft_lstsize(list) > 2)
	{
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
		return (ERROR);
	}
	exit_status = ft_long_atoi(tmp_list->content);
	if (errno)
		print_exit_error((char *)tmp_list->content);
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(exit_status);
	}
	return (SUCCESS);
}
