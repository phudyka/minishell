/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:10:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/11 15:05:31 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <curses.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "error.h"
# include "../libft/libft.h"

# define RESET "\x1b[0m"
# define GREEN "\x1b[32m"

extern int				g_signal;

typedef struct s_data	t_data;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	int			i;
	t_env		*env;
	t_data		*data;
}	t_pipe;

typedef struct s_token
{
	int				type;
	char			*value;
	char			*redir;
	char			*file;
	struct s_token	*next;
}	t_token;

typedef struct s_error
{
	int		status;
	bool	exit;
}	t_error;
typedef struct s_data
{
	int				fd[2];
	int				fd_in;
	char			**cmd;
	char			**path;
	char			**redir;
	char			*buffer;
	char			**cmd_parts;
	char			**strs;
	t_pipe			*pipes;
	t_token			*tokens;
	t_env			*env;
	t_error			*error;
	struct termios	*termios;
}	t_data;

typedef enum token
{
	QOT,
	RDR,
	PIP,
	STR,
	MLC,
}	t_enum_token;

void	ft_signals(t_data *data);
void	builtin_export(t_data *data, t_env *env);
void	builtin_env(t_env *env, char **cmd);
void	builtin_pwd(void);
int		is_only_space(char *cmd);
int		check_absolute(t_data *data);
int		is_builtin(t_data *data);
void	exec_builtin(t_data *data, t_env *env);
void	handle_builtin(t_data *data, t_env *env);
void	builtin_cd(t_data *data, t_env *env);
void	builtin_echo(t_data *data);
void	builtin_exit(t_data *data);
t_env	*envp_to_list(t_data *data, char **envp);
t_env	*create_node(t_data *data, char *var);
char	**split_command(t_data *data, int *len);
size_t	output_size(t_data *data, const char *str);
void	free_recmd(char **cmd, int start, int len);
char	*ft_reassign(t_token **tokens, char *cmd_arg);
void	print_list_token(t_token *env);
void	print_list(t_env *env);
void	print_list_export(t_env *env);
void	unset_list(t_env **env, char *var);
void	add_node(t_env **head, t_env *node);
int		search_in_env(t_env *env, char *variable);
char	*get_from_env(char *variable, t_env *env);
char	**list_to_array(t_env *head);
t_token	*new_token(t_enum_token type, char *value);
t_token	*tokenize_command(char **cmd, int cmd_len);
t_token	*tokenizer(char **cmd, int size, t_token *tokens);
void	add_token(t_token **tokens, t_token *new);
int		parse_redir(t_data *data, t_token *tokens);
void	parse_quotes(t_data *data, t_token *curr);
char	*command_status(const char *input);
char	*ft_dollar(t_data *data, const char *str, int sqot);
int		master_parser(t_data *data, t_token *token);
char	**master_lexer(t_data *data);
int		ft_equal(const char *s);
void	restore_termios(t_data *data);
char	**ft_split_buff(t_data *data);
char	*allocatenate(char *cmd, char *path);
char	**get_path(char **envp);
void	ft_prompt(t_data *data);
void	execute_pipeline(t_data *data, t_env *env);
char	*ft_access(char **path, char **cmd);
void	exec_cmd(t_data *data, char **envp);
void	process_command(t_data *data, t_env *env);
int		find_pipes(t_data *data);
void	handle_pipe_execution(t_data *data, t_env *env, int i);
void	read_next_command(t_data *data);
void	handle_parent_process(t_data *data);
void	exec_pipe_child(t_pipe *pipe_data);
t_pipe	*init_pipe_data(t_data *data, t_env *env, int i);
char	*read_line(void);
int		is_only_spaces_or_tabs(char *str);
void	handle_that_shit(char *next_command, t_data *data);
char	**cmd_parts(char **cmd_parts, char *new_command);
void	print_arguments(t_data *data, int start_index);
void	free_array(char **tab);
int		ft_pipex(char **cmd, char *path);
void	free_env(t_env *env);
void	free_data(t_data *data);
void	free_pipe(t_pipe *pipe_data);
void	free_buff(t_data *data);
void	free_tokens(t_token *tokens);
void	free_shell(void);
int		ft_equal(const char *s);
void	redirections(t_data *data, char **cmd);
void	execute_builtin_with_redirection(t_data *data, t_env *env);
char	*ft_strcpy(char *dest, const char *src);
void	parent_process(t_data *data, pid_t pid);
void	child_process(t_data *data, char **envp);
void	check_path_and_set_status(char *path, char **cmd);
char	**make_env(char **env, t_env *current);
char	*ft_access(char **path, char **cmd);
void	handle_variable(t_data *data, t_env **env);
int		update_var(t_env *env, char **variable, char *cmd_arg);
char	**get_variable(char *cmd_arg);
void	create_tmp_file(char *delimiter);
int		heredoc_line(char *line, ssize_t read, int fd, char *delimiter);
void	set_tmp_file_as_stdin(void);
void	exit_error(char *msg);
void	ft_error(t_error *error, int token, int code);
void	check_and_apply_redirection(t_data *data, char **cmd, int *i);
void	remove_redirection(char **cmd, int start);
int		redirect_output(t_data *data, char **cmd, int i, int append);
int		redirect_input(t_data *data, char **cmd, int i);
int		redirect_here_doc(char **cmd, int i);
void	init_error(t_error *error);
int		is_exit_command(char *cmd_part);
void	update_values(char *output, size_t *j, char *value);
bool	handle_mark(t_data *data, const char *str,
			char *output, size_t *indices);
size_t	get_var_len(const char *str, size_t i);
void	handle_segment(char **input, char **result, int *i, int *j);
void	add_result(char **result, char *temp, int *j);
char	*concat_strings(char *s1, char *s2);
char	**group_by_pipes(char **input);
int		exit_status(char *cmd);

#endif
