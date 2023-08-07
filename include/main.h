/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 05:52:38 by kali              #+#    #+#             */
/*   Updated: 2023/08/07 09:49:38 by kali             ###   ########.fr       */
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

#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"
typedef enum
{
    DOL, // dollar sign $
    QOT, // quotes : /' and /"
    RDR, // input '<' and truncate '>'
    PIP, // pipe '|'
    STR, // commande
}           token;
typedef struct  s_data
{
    pid_t   pid;
	int     fd[2];
    int     fd_in;
    char    **cmd;
    char    **path;
    char    **redir;
    char    *buffer;
	char    **cmd_parts;
}               t_data;
typedef struct  s_env
{
    char            *var;
    struct s_env   *next;
}               t_env;
typedef struct  s_pipe
{
    int     i;
	t_env   *env;
	t_data  *data;
}               t_pipe;
typedef struct s_token
{
	int		type;
	char	*value;
	char	*redir;
	char	*file;
	struct s_token	*next;
}	t_token;

typedef struct  s_shell
{
    int     status;
    t_env   *env;
    t_data  *data;
    t_pipe  *pipes;
    t_token *tokens;
}               t_shell;

extern t_shell g_shell;

//---------SIGNALS------------//
void    ft_signals(void);
//--------BUILTINS------------//
void    builtin_export(t_data *data, t_env *env);
void    builtin_env(t_env *env, char **cmd);
void    builtin_pwd(void);
int     is_builtin(t_data *data);
void    exec_builtin(t_data *data, t_env *env);
void    builtin_cd(char **path, t_env *env);
void    builtin_echo(t_data *data);
void    builtin_exit(void);
//----------LIST--------------//
t_env   *envp_to_list(char **envp);
t_env   *create_node(char *var);
void    print_list_token(t_token *env);
void    print_list(t_env *env);
void	print_list_export(t_env *env);
void    unset_list(t_env **env, char *var);
void    add_node(t_env **head, t_env *node);
int     search_in_env(t_env *env, char *variable);
char    *get_from_env(char *variable, t_env *env);
char    **list_to_array(t_env *head);
//---------PARSE-------------//
t_token *new_token(token type, char *value);
t_token *tokenize_command(char **cmd, int cmd_len);
t_token	*tokenizer(char **cmd, int size, t_token *tokens);
void	add_token(t_token **tokens, t_token *new);
void	parse_redir(t_token *tokens);
void	parse_quotes(t_token *tokens);
void    parse_dollar(t_token *tokens);
void    master_parser(t_token *token);
char    **master_lexer(char *buff);
//---------AUTRES------------//

char	**ft_split_buff(char const *s);
char	*allocatenate(char *cmd, char *path);
char	**get_path(char **envp);
void    ft_prompt(t_data *data, t_env *env);
void    execute_pipeline(t_data *data, t_env *env);
char    *ft_access(char **path, char **cmd);
void     exec_cmd(char *path, char **cmd, char **envp);
void    process_command(t_data *data, t_env *env);
int     find_pipes(t_data *data);
void	print_arguments(t_data *data, int start_index);
void    free_array(char **tab);
int     ft_pipex(char **cmd, char *path);
void    free_env(t_env *env);
void    free_data(t_data *data);
void    free_pipe(t_pipe *pipe_data);
void	free_buff(t_data *data);
void	free_tokens(t_token *tokens);
void	free_shell(void);
int    ft_equal(const char *s);
void    redirections(char **cmd);

#endif
