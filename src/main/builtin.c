/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 04:29:21 by kali              #+#    #+#             */
/*   Updated: 2023/08/10 10:13:35 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	builtin_env(t_env *env, char **cmd)
{
	if (!cmd[1])
		print_list(env);
	else
		printf("env: invalid option -- '%s'\n", cmd[1]);
}

void	builtin_echo(t_data *data)
{
	int	i;
	int	skip;

	i = 1;
	skip = 0;
	if (!data->cmd[i])
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strcmp(data->cmd[i], "-n") == 0)
	{
		skip = 1;
		i++;
	}
	print_arguments(data, i);
	if (!skip)
		write(1, "\n", 1);
}

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * PATH_MAX);
	if ((getcwd(cwd, PATH_MAX)))
		printf("%s\n", cwd);
	else
		perror ("pwd");
	if (cwd)
	{
		free (cwd);
		cwd = NULL;
	}
}

void	builtin_cd(char **path, t_env *env)
{
	char	*home;

	home = NULL;
	if (!path[1])
	{
		home = get_from_env("HOME", env);
		if (!home)
		{
			ft_putstr_fd("cd: $HOME not set\n", 2);
			g_shell.status = 1;
			return ;
		}
		chdir(home);
		free(home);
	}
	else
	{
		if (chdir(path[1]))
		{
			printf("cd: %s: No such file or directory\n", path[1]);
			g_shell.status = 127;
			return ;
		}
	}
}

void	builtin_export(t_data *data, t_env *env)
{
	if (!data->cmd[1])
	{
		print_list_export(env);
		return ;
	}
	handle_variable(data, &env);
}
