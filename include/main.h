/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 05:52:38 by kali              #+#    #+#             */
/*   Updated: 2023/06/13 10:49:00 by phudyka          ###   ########.fr       */
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

typedef struct  s_data
{
    char    **path;
    char    **cmd;
    char    *buffer;
}   t_data;

typedef struct  s_env
{
    char            *var;
    struct s_env   *next;
}   t_env;

//---------SIGNALS------------//
void    ft_signals(void);
//--------BUILTINS------------//
void    builtin_export(t_data *data, t_env *env);
void    builtin_exit(t_data *data, t_env *env);
void    builtin_env(t_env *env, char **cmd);
void    builtin_pwd(void);
int     is_builtin(t_data *data);
void    exec_builtin(t_data *data, t_env *env);
void    builtin_cd(char **path, t_env *env);
//----------LIST--------------//
t_env   *envp_to_list(char **envp);
t_env   *create_node(char *var);
void    print_list(t_env *env);
void    free_list(t_env *env);
void    unset_list(t_env **env, char *var);
void    add_node(t_env **head, t_env *node);
int     search_in_env(t_env *env, char *variable);
char    *get_from_env(char *variable, t_env *env);
//---------AUTRES------------//
void    ft_prompt(t_data *data, t_env *env);
void    free_array(char **tab);

#endif