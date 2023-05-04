/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 05:52:38 by kali              #+#    #+#             */
/*   Updated: 2023/05/04 14:43:12 by phudyka          ###   ########.fr       */
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
    char            **path;
    char            **cmd;
    char            *buffer;
    struct s_data   *next;
}               t_data;

void    ft_signals(void);
void    builtin_pwd(void);
int     is_builtin(char *cmd);
void    exec_builtin(char **cmd);
void    builtin_cd(char *path);
void    ft_prompt(t_data *data);
t_data  *ft_init_data(char **envp);
void    free_tab(char *tab);
void    free_ttab(char **tab);
void    free_data(t_data *data);

#endif