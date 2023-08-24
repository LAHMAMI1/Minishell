/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 23:18:38 by olahmami          #+#    #+#             */
/*   Updated: 2023/08/21 16:13:21 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_execution
{
	char		**split_cmds;
	char		**env;
	char		**split_env;
	char		*executable;
	int			fd[2];
	int			fdin;
	int			fdout;
	int			outfile;
	pid_t		pid;
	int			size_cmds;
	int			tmp_in;
	int			tmp_out;
	t_cmd_file	*cmd_file;
	t_in_out_fd	in_out_fd;
	t_list		*cmds;
	int			flag;
	int			i;
}				t_execution;

void			global_executor(t_list *list, t_execution *executor);
char			**convert_linkedlist_to_char_arr_cmd(t_list *cmds);
char			**read_env(char **env, char **split_cmds);
char			*cmd_extand(char **split_path, char *executable,
					char **split_cmds);
void			execution(char **env, char *executable, char **split_cmds);
void			close_if_not(int fd, int rtrn);
char			**read_path(char **split_cmds, char **split_path, char *path);
void			check_directory(char **split_cmds, int dir);
void			check_error(char **split_cmds);
void			execute_one_builtin(t_execution *executor, int *status);
void			fd_in(t_execution *executor);
void			fd_out(t_execution *executor);
void			open_pipe(t_execution *executor);
void			child_execute(t_execution *executor, int *status);
void			fork_process(t_execution *executor, int *status, t_list *tmp);
void			save_and_close(t_execution *executor);
void			waiting(t_execution *executor, int *status);
void			init_execution(t_execution *executor, t_list *list,
					int *status);
void			dup_after_pipe(t_execution *executor);
void			execute_all_cmd(t_execution *executor, int *status, t_list *tmp,
					t_list *list);
int				ft_counter(const char *s, char c);
char			**ft_split_exec(char const *s, char c);
char			*ft_strjoin_exec(char *s1, char *s2);
#endif