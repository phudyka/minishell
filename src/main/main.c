/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:06 by kali              #+#    #+#             */
/*   Updated: 2023/08/22 11:59:06 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	g_signal = 0;

static char	*ft_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_strdup(envp[i] + 5));
}

char	**get_path(char **envp)
{
	int		i;
	char	*path;
	char	**final_path;

	i = -1;
	path = NULL;
	final_path = NULL;
	path = ft_path(envp);
	if (!path)
		return (NULL);
	final_path = ft_split(path, ':');
	free(path);
	while (final_path[++i])
		final_path[i] = ft_strjoin(final_path[i], "/");
	return (final_path);
}

char	**make_env(char **env, t_env *current)
{
	int	i;

	i = 0;
	while (current)
	{
		env[i] = ft_strdup(current->var);
		if (!env[i])
			exit(EXIT_FAILURE);
		current = current->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

static void	init_data(t_data *data, char **envp)
{
	if (data)
	{
		data->env = envp_to_list(data, envp);
		data->buffer = NULL;
		data->cmd = NULL;
		data->cmd_parts = NULL;
		data->path = get_path(envp);
		data->error = malloc(sizeof(t_error));
		data->error->status = 0;
		data->error->exit = 0;
	}
	else
	{
		ft_putstr_fd("Error! [failed to init data]\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	init_data(data, envp);
	ft_signals(data);
	ft_prompt(data);
	restore_termios(data);
	free_env(data->env);
	free(data->error);
	free(data);
	ft_putstr_fd("exit\n", 1);
	return (0);
}
