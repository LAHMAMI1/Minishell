/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:25:51 by olahmami          #+#    #+#             */
/*   Updated: 2023/08/21 17:51:59 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**convert_linkedlist_to_char_arr_cmd(t_list *cmds)
{
	int		size;
	char	**char_array;
	t_list	*current;
	int		i;

	size = ft_lstsize(cmds);
	char_array = (char **)malloc((size + 1) * sizeof(char *));
	if (!char_array)
		return (NULL);
	char_array[size] = NULL;
	current = cmds;
	i = 0;
	while (current != NULL)
	{
		char_array[i] = (char *)(current->content);
		current = current->next;
		i++;
	}
	return (char_array);
}

void	check_directory(char **split_cmds, int dir)
{
	if (split_cmds[0][0] == '.' && split_cmds[0][1] == '\0')
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		close(dir);
		exit(2);
	}
	else if (split_cmds[0][0] == '.' && split_cmds[0][1] == '.'
			&& split_cmds[0][2] != '/')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(split_cmds[0], 2);
		ft_putstr_fd(": Command not found.\n", 2);
		exit(127);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(split_cmds[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		close(dir);
		exit(126);
	}
}

void	check_error(char **split_cmds)
{
	int	end_cmd;

	end_cmd = ft_strlen(split_cmds[0]) - 1;
	if (access(split_cmds[0], F_OK) && split_cmds[0][end_cmd] == '/')
	{
		ft_putstr_fd("minishell: ", 2);
		perror(split_cmds[0]);
		exit(126 + (errno == ENOENT));
	}
	else if (access(split_cmds[0], F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(split_cmds[0]);
		exit(127);
	}
	else if (access(split_cmds[0], F_OK | X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(split_cmds[0]);
		exit(126);
	}
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_exec(char *s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*p;

	if (!s1 || !s2)
		return (0);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	p = (char *)malloc(s1len + s2len + 1);
	if (!p)
		return (0);
	else
	{
		ft_strncpy(p, s1, s1len);
		ft_strncpy(p + s1len, s2, s2len + 1);
	}
	return (p);
}
