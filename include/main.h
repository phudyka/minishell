/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:21:15 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 22:46:53 by phudyka          ###   ########.fr       */
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

typedef enum token
{
	QOT,
	RDR,
	PIP,
	STR,
}	t_enum_token;

typedef struct s_data
{
	int		fd[2];
	int		fd_in;
	char		**cmd;
	char		**path;
	char		**redir;
	char		*buffer;
	char		**cmd_parts;
}	t_data;

typedef struct s_env
{
	char				*var;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	int		i;
	t_env		*env;
	t_data	*data;
}	t_pipe;

typedef struct s_token
{
	int				type;
	char				*value;
	char				*redir;
	char				*file;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	int				status;
	bool			exit_status;
	pid_t				pid;
	t_env				*env;
	t_data			*data;
	t_pipe			*pipes;
	t_token			*tokens;
	struct termios	*termios;
}	t_shell;

extern t_shell	g_shell;

void		ft_signals(void);
void		builtin_export(t_data *data, t_env *env);
void		builtin_env(t_env *env, char **cmd);
void		builtin_pwd(void);
int         is_builtin(t_data *data);
void		exec_builtin(t_data *data, t_env *env);
void		handle_builtin(t_data *data, t_env *env);
void		builtin_cd(char **path, t_env *env);
void		builtin_echo(t_data *data);
void		builtin_exit(void);
t_env		*envp_to_list(char **envp);
t_env		*create_node(char *var);
char		**split_command(char *buff, int *len);
size_t		output_size(const char *str);
void		free_recmd(char **cmd, int start, int len);
char		*ft_reassign(t_token **tokens, char *cmd_arg);
void		print_list_token(t_token *env);
void		print_list(t_env *env);
void		print_list_export(t_env *env);
void		unset_list(t_env **env, char *var);
void		add_node(t_env **head, t_env *node);
int		search_in_env(t_env *env, char *variable);
char		*get_from_env(char *variable, t_env *env);
char		**list_to_array(t_env *head);
t_token		*new_token(t_enum_token type, char *value);
t_token		*tokenize_command(char **cmd, int cmd_len);
t_token		*tokenizer(char **cmd, int size, t_token *tokens);
void		add_token(t_token **tokens, t_token *new);
void		parse_redir(t_token *tokens);
void		parse_quotes(t_token *curr);
char		*command_status(const char *input);
char		*ft_dollar(const char *str, int sqot);
void		master_parser(t_token *token);
char		**master_lexer(char *buff);
int			ft_equal(const char *s);
void		restore_termios(void);
char		**ft_split_buff(char const *s);
char		*allocatenate(char *cmd, char *path);
char		**get_path(char **envp);
void		ft_prompt(t_data *data, t_env *env);
void		execute_pipeline(t_data *data, t_env *env);
char		*ft_access(char **path, char **cmd);
void		exec_cmd(char *path, char **cmd, char **envp);
void		process_command(t_data *data, t_env *env);
int			find_pipes(t_data *data);
void		redirections(char **cmd);
void		print_arguments(t_data *data, int start_index);
void		free_array(char **tab);
int			ft_pipex(char **cmd, char *path);
void		free_env(t_env *env);
void		free_data(t_data *data);
void		free_pipe(t_pipe *pipe_data);
void		free_buff(t_data *data);
void		free_tokens(t_token *tokens);
void		free_shell(void);
int			ft_equal(const char *s);
void		redirections(char **cmd);
void		execute_builtin_with_redirection(t_data *data, t_env *env);
char		*ft_strcpy(char *dest, const char *src);
void		parent_process(pid_t pid);
void		child_process(char *path, char **cmd, char **envp);
void		check_path_and_set_status(char *path, char **cmd);
char		**make_env(char **env, t_env *current);
char		*ft_access(char **path, char **cmd);
void		handle_variable(t_data *data, t_env **env);
int			update_var(t_env *env, char **variable, char *cmd_arg);
char		**get_variable(char *cmd_arg);
void		create_tmp_file(char *delimiter);
void		heredoc_line(char *line, ssize_t read, int fd, char *delimiter);
void		set_tmp_file_as_stdin(void);
void		exit_error(char *msg);
void		check_and_apply_redirection(char **cmd, int *i);
void		remove_redirection(char **cmd, int start);
int			redirect_output(char **cmd, int i, int append);
int			redirect_input(char **cmd, int i);
void		redirect_here_doc(char **cmd, int i);

#endif
