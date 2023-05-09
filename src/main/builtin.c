/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 04:29:21 by kali              #+#    #+#             */
/*   Updated: 2023/05/06 09:12:30 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void    builtin_env(t_env *env)
{
    afficher_liste(env);
}

void    builtin_pwd(void)
{
    char    *cwd;

    cwd = malloc(sizeof(char) * PATH_MAX);
    if ((getcwd(cwd, PATH_MAX)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
    if (cwd)
    {
        free (cwd);
        cwd = NULL;
    }
}

void    builtin_cd(char **path)
{
    char    *home;

    home = NULL;
    if (path[1] == NULL)
    {
        home = getenv("HOME");
        if (home == NULL)
        {
            printf("cd: $HOME not set\n");
            return ;
        }
        chdir(home);
    }
    else
    {
        if (chdir(path[1]) != 0)
        {
            printf("cd: %s: No such file or directory\n", path[1]);
            return ;
        }
    }
}

void    exec_builtin(char **cmd, t_env *env)
{
    if ((ft_strcmp(cmd[0], "cd")) == 0)
        builtin_cd(cmd);
    else if ((ft_strcmp(cmd[0], "pwd")) == 0)
        builtin_pwd();
    else if ((ft_strcmp(cmd[0], "env")) == 0)
        builtin_env(env);
    else if ((ft_strcmp(cmd[0], "unset")) == 0)
        unset_list(&env, cmd[1]);
    else if ((ft_strcmp(cmd[0], "exit")) == 0) // A Faire (tout free et exit)
        exit(EXIT_SUCCESS);
}

int is_builtin(char *cmd)
{
    char    **all_cmd;
    int     i;
    int     res;

    i = 0;
    res = 1;
    all_cmd = malloc(sizeof(char *) * 6);
    all_cmd[0] = "cd";
    all_cmd[1] = "pwd";
    all_cmd[2] = "env";
    all_cmd[3] = "unset";
    all_cmd[4] = "exit";
    all_cmd[5] = NULL;
    while (all_cmd[i])
    {
        if ((ft_strcmp(all_cmd[i], cmd)) == 0)
            res = 0;
        i++;
    }
    if (all_cmd)
    {
        free (all_cmd);
        all_cmd = NULL;
    }
    return (res);
}