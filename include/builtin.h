/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:15:48 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 15:15:59 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "../libft/libft.h"
# include "parser.h"

# define ERROR 1
# define SUCCESS 0

int		check_builtin(t_cmd_file cmd_file);
int		builtin(t_cmd_file cmd_file, int *flag);
int		replace_env_var_if_exist(char *str);
int		is_unvalid_name(char *var_name);
int		ft_echo(t_list *list);

void	signal_handler(int sig);
int		ft_export(t_list *list);
int		ft_unset(t_list *list_cmd);
int		ft_env(t_list *list_cmd);
int		ft_pwd(void);
int		ft_exit(t_list *list);
int		ft_cd(t_list *list);
int		should_be_join(char *str);
void	sort_env(char **env_arr, int size);
void	print_var(char *str);
int		is_unvalid_var_name(char *str);
int		is_unvalid_name(char *var_name);
int		var_was_replace_or_join(char *str, int plus_index);
void	replace_or_join(char *str, int plus_index);
int		replace_env_var_if_exist2(char *str, t_list *tmp);
int		replace_env_var_if_exist(char *str);
#endif
