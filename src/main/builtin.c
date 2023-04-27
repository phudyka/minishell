/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 04:29:21 by kali              #+#    #+#             */
/*   Updated: 2023/04/27 14:21:04 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void    builtin_pwd(void)
{
    char    *cwd;

    cwd = malloc(sizeof(char) * PATH_MAX);
    if ((getcwd(cwd, PATH_MAX)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
    /*if (cwd)
    {
        free (cwd);
        cwd = NULL;
    }*/
}

void    builtin_cd(char *path)
{
    if ((chdir(path) == -1))
        perror("cd");
}

void    exec_builtin(char **cmd)
{
    if ((ft_strcmp(cmd[0], "cd")) == 0)
        builtin_cd(cmd[1]);
    else if ((ft_strcmp(cmd[0], "pwd")) == 0)
        builtin_pwd();
}

int is_builtin(char *cmd)
{
    char    **all_cmd;
    int     i;
    int     res;

    i = 0;
    res = 1;
    all_cmd = malloc(sizeof(char *) * 3);
    all_cmd[0] = "cd";
    all_cmd[1] = "pwd";
    all_cmd[2] = NULL;
    while (all_cmd[i])
    {
        if ((ft_strcmp(all_cmd[i], cmd)) == 0)
            res = 0;
        i++;
    }
    /*if (all_cmd)
    {
        free( all_cmd);
        all_cmd = NULL;
    }*/
    return (res);
}