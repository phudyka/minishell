/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:18:07 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/13 03:00:51 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/error.h"

void	exec_builtin(t_data *data, t_env *env)
{
	if ((ft_strcmp(data->cmd[0], "cd")) == 0)
		builtin_cd(data, env);
	else if ((ft_strcmp(data->cmd[0], "pwd")) == 0)
		builtin_pwd();
	else if ((ft_strcmp(data->cmd[0], "env")) == 0)
		builtin_env(env, data->cmd);
	else if ((ft_strcmp(data->cmd[0], "unset")) == 0)
		unset_list(&env, data->cmd[1]);
	else if ((ft_strcmp(data->cmd[0], "exit")) == 0)
		builtin_exit(data);
	else if ((ft_strcmp(data->cmd[0], "export")) == 0)
		builtin_export(data, env);
	else if ((ft_strcmp(data->cmd[0], "echo") == 0)
		|| (ft_strcmp(data->cmd[0], "echo") == 0
			&& ft_strcmp(data->cmd[1], "-n") == 0))
		builtin_echo(data);
}

static void	free_cmd(char **all)
{
	if (!all)
		return ;
	free(all);
	all = NULL;
}

static char	**set_cmd(void)
{
	char	**all;

	all = (char **)malloc(sizeof(char *) * 8);
	if (!all)
		return (NULL);
	all[0] = "cd";
	all[1] = "pwd";
	all[2] = "env";
	all[3] = "unset";
	all[4] = "exit";
	all[5] = "export";
	all[6] = "echo";
	all[7] = NULL;
	return (all);
}

int	is_builtin(t_data *data)
{
	int		i;
	int		res;
	char	**all;

	i = -1;
	res = 1;
	all = set_cmd();
	if (!all)
	{
		ft_error(data->error, MLC, 0);
		return (0);
	}
	while (all[++i])
	{
		if ((ft_strcmp(all[i], data->cmd[0])) == 0)
			res = 0;
	}
	free_cmd(all);
	return (res);
}

void	handle_builtin(t_data *data, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		handle_multi_redirections(data);
		exec_builtin(data, env);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		ft_putstr_fd("Error ! [fork]\n", 2);
		data->error->status = 35;
	}
}
