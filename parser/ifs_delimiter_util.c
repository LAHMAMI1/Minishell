/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs_delimiter_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:58:07 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/19 11:56:21 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	init_delimiter_array(int *delimiter_arr, const char *delimiter)
{
	ft_memset(delimiter_arr, 0, sizeof(int) * 256);
	while (*delimiter)
	{
		delimiter_arr[(int)*delimiter] = 1;
		if (ft_isspace(*delimiter))
			delimiter_arr[(int)*delimiter] = 2;
		delimiter++;
	}
}

int	skip_delimeter(const char *str, int i, int *delimiter_arr)
{
	int	is_in_delimeter;

	is_in_delimeter = 0;
	while (str[i])
	{
		if (delimiter_arr[(int)str[i]] == 0 || (delimiter_arr[(int)str[i]] == 1
				&& is_in_delimeter == 1))
			break ;
		if (delimiter_arr[(int)str[i]] == 1)
			is_in_delimeter = 1;
		i++;
	}
	return (i);
}
