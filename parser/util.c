/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:38:18 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/19 19:11:15 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

void	init_variables(int *i, int *j, int *pt)
{
	*i = 0;
	*j = 0;
	*pt = 0;
}

int	is_redirection(t_type type)
{
	return ((type == TOKEN_REDIRECT_INPUT || type == TOKEN_REDIRECT_OUTPUT
			|| type == TOKEN_HEREDOC || type == TOKEN_REDIRECT_APPEND));
}

int	is_spicial(t_type type)
{
	return (type != TOKEN_END && type != TOKEN_ERROR && type != TOKEN_PIPE);
}

void	close_if_not(int fd, int rtrn)
{
	if (fd != rtrn)
		close(fd);
}
