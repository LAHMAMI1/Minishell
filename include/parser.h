/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiraa <fdiraa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:16:22 by fdiraa            #+#    #+#             */
/*   Updated: 2023/08/20 15:25:09 by fdiraa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../libft/libft.h"
# define EOF_ERROR "warning: here-document delimited by end-of-file (wanted `"

typedef enum s_type
{
	TOKEN_REDIRECT_INPUT,
	TOKEN_REDIRECT_OUTPUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_END,
	TOKEN_WORD,
	TOKEN_ERROR
}					t_type;

typedef enum s_redirec_type
{
	REDIRECTION_INPUT,
	REDIRECTION_OUTPUT,
	REDIRECTION_APPEND,
	REDIRECTION_HEREDOC,
}					t_redirec_type;

typedef struct s_token
{
	char			*value;
	t_type			type;

}					t_token;

typedef struct s_redirection
{
	char			*file_name;
	t_redirec_type	redic_type;
}					t_redirection;

typedef struct s_in_out_fd
{
	int				in_fd;
	int				out_fd;
}					t_in_out_fd;
typedef struct s_cmd_file
{
	t_list			*cmds;
	t_list			*redirection;
	char			*error;
	t_in_out_fd		in_out_fd;
	int				pipe_has_error;
	int				exit_by_signal;
}					t_cmd_file;
typedef struct s_list_pt
{
	t_list			*current;
	t_list			*previous;
	t_list			*nextnode;
	t_list			*list;
}					t_list_pt;

typedef struct s_ifs_exp
{
	int				i;
	int				j;
	char			*var_name;
	char			*str;
	int				has_quote;
}					t_ifs_exp;
void				print_cmd(t_cmd_file cmd_file);

void				print_args(void *content);
void				free_t_cmd_file(void *arg);
t_cmd_file			get_cmd(const char **str);

char				*replace_word(const char *str, int index, int size,
						const char *replacement);

void				*ft_realloc(void *ptr, size_t size);
int					compair_arr_strings(const char **arr_1, const char **arr_2);
char				**field_splitting(const char *str, const char *characters);

void				init_variables(int *i, int *j, int *pt);

char				*extract_name(char *var);
const char			*get_env_var_value(const char *var);
void				ifs_expander(t_list *list, char *ifs);
char				*remove_single_quotes(char *str, int *i, int *has_quote);
char				*remove_double_quotes(char *str, int *i, int to_be_expand,
						int *has_quote);
int					start_with_only_whitspace(const char *str, char *delimiter);
int					end_with_only_whitspace(const char *str, char *delimiter);
int					expand_cmd_list(t_cmd_file *cmd_file, char *ifs);
char				*do_ifs_expander(t_list **new_list, char *word);
int					file_expander(t_list *list, int *hd_has_quotes);
t_list				*get_env_variables(const char **env);
void				unset_var_env(t_list **env, char *content);
t_list				*global_parser(const char *str);
t_list				*get_env_variables(const char **env);
void				handle_sigint(int sig);
void				extract_in_out_fd(t_cmd_file *cmd_file, int hd_has_quotes);
void				readFile(int fd);
char				**convert_linkedlist_to_char_arr(void);
int					join_and_replace(char *var_name, char *var_value);
int					update_exit_status_var(int status_value);
int					is_special(char c);
int					find_closing_qq(const char *str);
t_token				get_word(const char **str);
void				init_delimiter_array(int *delimiter_arr,
						const char *delimiter);
int					skip_delimeter(const char *str, int i, int *delimiter_arr);
int					is_redirection(t_type type);
int					is_spicial(t_type type);
void				expande_node(t_list *list, t_list *new_list);
char				*concat_leftouvers(char *str, char *word, int i, int j);
void				push_if_not_empty(t_list **new_list, char *str,
						int *has_quote);
char				*word_split_to_node(t_list **new_list,
						const char *var_value,	char *str, int *has_quote);

const char			*get_var_value(char *var_name);
void				herd_sig(int sig);
void				redirect_in(t_cmd_file *cmd_file, char *filename);
void				redirect_append(t_cmd_file *cmd_file, char *filename);
void				redirect_out(t_cmd_file *cmd_file, char *filename);
void				redirect_herdoc(t_cmd_file *cmd_file, int here_doc_fd);
char				*expand_heredoc_vars(char *var);
int					open_here_doc(t_cmd_file *cmd_file, int hd_has_quotes);
int					last_in_file(t_cmd_file *cmd_file);
t_redirection		*make_redirect(t_cmd_file *cmd_file, t_token *token,
						const char **str);
void				set_error_msg(t_cmd_file *cmd_file, t_token *token,
						const char **str);
void				free_redir(void *ptr);
void				free_t_cmd_file(void *arg);

#endif
