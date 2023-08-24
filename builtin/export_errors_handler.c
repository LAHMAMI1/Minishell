/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:02:47 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/18 15:20:33 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void	print_var(char *str)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (str[i] && str[i] != '=')
	{
		printf("%c", str[i]);
		i++;
	}
	if (str[i] && str[i] == '=' && str[i + 1])
	{
		printf("=\"");
		printf("%s", str + i + 1);
		printf("\"");
	}
	else if (str[i] && str[i] == '=' && !str[i + 1])
	{
		printf("=\"\"");
	}
	printf("\n");
}

void	sort_env(char **env_arr, int size)
{
	int	swapped;
	int	i;
	int	j;

	while (size > 1)
	{
		swapped = 0;
		i = 0;
		j = 1;
		while (j < size)
		{
			if (ft_strcmp_char(env_arr[i], env_arr[j], '=') > 0)
			{
				ft_swap_strings(&env_arr[i], &env_arr[j]);
				swapped = 1;
			}
			i++;
			j++;
		}
		if (!swapped)
			break ;
		size--;
	}
}

int	should_be_join(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (str[i] == '+' && str[i + 1] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	is_unvalid_var_name(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (str[i] == '+' && str[i + 1] == '=')
			return (0);
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_unvalid_name(char *var_name)
{
	if (var_name[0] >= 'A' && var_name[0] <= 'Z')
		return (0);
	else if (var_name[0] >= 'a' && var_name[0] <= 'z')
		return (0);
	else if (var_name[0] == '_')
		return (0);
	return (1);
}
