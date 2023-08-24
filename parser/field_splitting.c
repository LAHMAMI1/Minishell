/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:27:56 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 00:00:14 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	**delimit(char **field_splited, const char *str, int size, int pt)
{
	char	**new_field;

	field_splited[pt - 1] = ft_dup(str, size);
	new_field = ft_calloc(pt + 1, sizeof(char *));
	if (!new_field)
		exit(1);
	ft_memcpy(new_field, field_splited, pt * sizeof(char *));
	free(field_splited);
	return (new_field);
}

char	**field_splitting_util(const char *str, int *delimiter_arr)
{
	char	**field_splited;
	int		i;
	int		j;
	int		pt;

	init_variables(&i, &j, &pt);
	field_splited = malloc(sizeof(char *));
	if (!field_splited)
		return (NULL);
	while (str[i])
	{
		if (delimiter_arr[(int)str[i]] == 0)
		{
			i++;
			continue ;
		}
		field_splited = delimit(field_splited, str + j, i - j, ++pt);
		i = skip_delimeter(str, i, delimiter_arr);
		j = i;
	}
	if (j != i)
		field_splited = delimit(field_splited, str + j, i - j, ++pt);
	field_splited[pt] = NULL;
	return (field_splited);
}

char	**field_splitting(const char *str, const char *delimiter)
{
	int	delimiter_arr[256];

	init_delimiter_array(delimiter_arr, delimiter);
	if (!str)
		return (NULL);
	while (*str && delimiter_arr[(int)*str] == 2)
		str++;
	return (field_splitting_util(str, delimiter_arr));
}

int	start_with_only_whitspace(const char *str, char *delimiter)
{
	int	delimiter_arr[256];
	int	ws_is_found;

	ws_is_found = 0;
	init_delimiter_array(delimiter_arr, delimiter);
	if (!str)
		return (0);
	while (*str && delimiter_arr[(int)*str] == 2)
	{
		ws_is_found = 1;
		str++;
	}
	return (delimiter_arr[(int)*str] == 0 && ws_is_found);
}

int	end_with_only_whitspace(const char *str, char *delimiter)
{
	int	delimiter_arr[256];
	int	ws_is_found;
	int	len;

	ws_is_found = 0;
	if (!str || ft_strlen(str) == 0)
		return (0);
	len = ft_strlen(str) - 1;
	init_delimiter_array(delimiter_arr, delimiter);
	while (str[len] && delimiter_arr[(int)str[len]] == 2)
	{
		ws_is_found = 1;
		len--;
	}
	return (delimiter_arr[(int)str[len]] == 0 && ws_is_found);
}
