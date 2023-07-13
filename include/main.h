/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 05:52:38 by kali              #+#    #+#             */
/*   Updated: 2023/07/13 16:53:32 by phudyka          ###   ########.fr       */
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
# include "error.h"
# include "../libft/libft.h"

# define RESET "\x1b[0m"
# define GREEN "\x1b[32m"

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

typedef struct s_pipe_data
{
	int		i;
	t_env	*env;
	t_data	*data;
}				t_pipe_data;

void	ft_signals(t_data *data, t_env *env, t_token *tokens);
void	builtin_export(t_data *data, t_env *env);
void	builtin_exit(t_data *data, t_env *env, t_token *token);
void	builtin_env(t_env *env, char **cmd);
void	builtin_pwd(void);
int		is_builtin(t_data *data);
void	exec_builtin(t_data *data, t_env *env);
void	builtin_cd(char **path, t_env *env);
void	builtin_echo(t_data *data);
t_env	*envp_to_list(char **envp);
t_env	*create_node(char *var);
void	print_list_token(t_token *env);
void	print_list(t_env *env);
void	free_list(t_env *env);
void	unset_list(t_env **env, char *var);
void	add_node(t_env **head, t_env *node);
int		search_in_env(t_env *env, char *variable);
char	*get_from_env(char *variable, t_env *env);
char	**list_to_array(t_env *head);
char	*allocatenate(char *cmd, char *path);
char	**get_path(char **envp);
void	ft_prompt(t_data *data, t_env *env, t_token *tokens);
void	execute_pipeline(t_data *data, t_env *env);
char	*ft_access(char **path, char **cmd);
void	exec_cmd(char *path, char **cmd, char **envp);
void	process_command(t_data *data, t_env *env);
int		find_pipes(t_data *data);
int		ft_pipex(char **cmd, char *path);
void	free_data(t_data *data);
void	free_buff(t_data *data);
void	free_array(char **tab);
void	free_shell(t_data *data, t_env *env);

#endif
