/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 05:52:38 by kali              #+#    #+#             */
/*   Updated: 2023/07/15 11:50:16 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MAIN_H
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
# include "parser.h"
# include "expander.h"
# include "error.h"
# include "../libft/libft.h"

# define RESET "\x1b[0m"
# define GREEN "\x1b[32m"
typedef enum id
{
	QOT,
	RDR,
	PIP,
	STR,
}			t_id;
typedef struct s_data
{
	int		fd[2];
	int		fd_in;
	char	**cmd;
	char	**path;
	char	**redir;
	char	*buffer;
	char	**cmd_parts;
}			t_data;
typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}				t_env;
typedef struct s_pipe
{
	int		i;
	t_env	*env;
	t_data	*data;
}				t_pipe;
typedef struct s_token
{
	t_id			type;
	char			*value;
	struct s_token	*next;
}			t_token;
typedef struct	s_shell
{
	t_env		*env;
	t_data		*data;
	t_pipe		*pipes;
	t_token		*tokens;
}				t_shell;

void	ft_signals(t_shell *shell);
void	builtin_export(t_data *data, t_env *env);
void	ft_export(char **variable, t_data *data, t_env *current);
void	builtin_exit(t_shell *shell);
void	builtin_env(t_env *env, char **cmd);
void	builtin_pwd(void);
void	builtin_cd(char **path, t_env *env);
void	builtin_echo(t_data *data);
int		is_builtin(t_shell *shell);
void	print_arguments(t_data *data, int start_index);
void	exec_builtin(t_shell *shell);
t_env	*envp_to_list(char **envp);
t_env	*create_node(char *var);
void	print_list_token(t_token *env);
void	print_list(t_env *env);
void	unset_list(t_env **env, char *var);
void	add_node(t_env **head, t_env *node);
void	parse_redir(t_shell *shell);
void	parse_quotes(t_token *tokens, t_shell *shell);
void	master_parser(t_token *tokens, t_shell *shell);
char	**master_lexer(char *buff, t_shell *shell);
void	free_tokens(t_token *tokens);
int		search_in_env(t_env *env, char *variable);
char	*get_from_env(char *variable, t_env *env);
char	**list_to_array(t_env *head);
char	*allocatenate(char *cmd, char *path);
char	**get_path(char **envp);
void	ft_prompt(t_shell *shell);
void	execute_pipeline(t_shell *shell);
char	*ft_access(char **path, char **cmd);
void	exec_cmd(char **envp, t_shell *shell);
void	process_command(t_shell *shell);
int		find_pipes(t_data *data);
int		ft_pipex(char **cmd, char *path);
void    redirections(char **cmd);
void	free_data(t_data *data);
void	free_list(t_env *env);
void	free_buff(t_data *data);
void	free_array(char **tab);
void	free_shell(t_shell *shell);

#endif
