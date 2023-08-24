/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:40:35 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 13:15:10 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <limits.h>
#include <linux/limits.h>
#include <unistd.h>

int	ft_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		buffer = (char *)get_env_var_value("PWD");
		if (!buffer)
		{
			ft_putstr_fd("Can't find current directory\n", 2);
			return (ERROR);
		}
		printf("%s\n", buffer);
	}
	else
	{
		printf("%s\n", buffer);
		free(buffer);
	}
	return (SUCCESS);
}
