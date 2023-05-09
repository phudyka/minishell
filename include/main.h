/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 05:52:38 by kali              #+#    #+#             */
/*   Updated: 2023/05/09 09:20:21 by phudyka          ###   ########.fr       */
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
# include "../libft/libft.h"


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

void    ft_signals(void);
void    builtin_pwd(void);
int     is_builtin(char *cmd);
void    exec_builtin(char **cmd, t_env *env);
void    builtin_cd(char **path);
void    ft_prompt(t_data *data, t_env *env);
void    free_array(char **tab);
t_env   *envp_to_list(char **envp);
void	afficher_liste(t_env *env);
void    free_list(t_env *env);
void	unset_list(t_env **env, char *var);

#endif