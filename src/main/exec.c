/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:18:07 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/30 16:27:03 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void    exec_builtin(t_data *data, t_env *env)
{
        if ((ft_strcmp(data->cmd[0], "cd")) == 0)
                builtin_cd(data->cmd, env);
        else if ((ft_strcmp(data->cmd[0], "pwd")) == 0)
                builtin_pwd();
        else if ((ft_strcmp(data->cmd[0], "env")) == 0)
                builtin_env(env, data->cmd);
        else if ((ft_strcmp(data->cmd[0], "unset")) == 0)
                unset_list(&env, data->cmd[1]);
        else if ((ft_strcmp(data->cmd[0], "exit")) == 0)
                builtin_exit(data, env);
        else if ((ft_strcmp(data->cmd[0], "export")) == 0)
                builtin_export(data, env);
}

int     is_builtin(t_data *data)
{
        int     i;
        int     res;
        char    **all_cmd;

        i = 0;
        res = 1;
        all_cmd = malloc(sizeof(char *) * 7);
        all_cmd[0] = "cd";
        all_cmd[1] = "pwd";
        all_cmd[2] = "env";
        all_cmd[3] = "unset";
        all_cmd[4] = "exit";
        all_cmd[5] = "export";
        all_cmd[6] = NULL;
        while (all_cmd[i])
        {
                if ((ft_strcmp(all_cmd[i], data->cmd[0])) == 0)
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