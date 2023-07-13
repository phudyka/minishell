/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 04:29:21 by kali              #+#    #+#             */
/*   Updated: 2023/07/13 11:58:10 by phudyka          ###   ########.fr       */
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

void	builtin_exit(t_data *data, t_env *env)
{
	if (data)
	{
		free_array(data->cmd);
		free_array(data->path);
		free (data->buffer);
		free (data);
	}
	if (env)
		free_list(env);
	exit (EXIT_SUCCESS);
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
			printf ("cd: $HOME not set\n");
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
			return ;
		}
	}
}

void	builtin_export(t_data *data, t_env *env)
{
	char	**variable;
	t_env	*current;
	t_env	*new_variable;

	variable = NULL;
	if (!data->cmd[1])
		return ;
	current = env;
	variable = ft_split(data->cmd[1], '=');
	while (current)
	{
		if (ft_strncmp(current->var,
				variable[0], ft_strlen(variable[0])) == 0)
		{
			free(current->var);
			free_array(variable);
			current->var = strdup(data->cmd[1]);
			return ;
		}
		current = current->next;
	}
	if (variable)
		free_array(variable);
	new_variable = create_node(data->cmd[1]);
	add_node(&env, new_variable);
}
