/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 05:52:38 by kali              #+#    #+#             */
/*   Updated: 2023/04/20 16:02:51 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MAIN_H
# define MAIN_H

# include <stdio.h>
# include <errno.h>
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

void    ft_prompt(t_data *data);
void    free_array(char **tab);

#endif