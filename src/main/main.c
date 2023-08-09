/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:06 by kali              #+#    #+#             */
/*   Updated: 2023/08/09 22:48:27 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

t_shell	g_shell;

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

static void	init_data(char **envp)
{
	g_shell.data = malloc(sizeof(t_data));
	if (g_shell.data)
	{
		g_shell.data->buffer = NULL;
		g_shell.data->cmd = NULL;
		g_shell.data->cmd_parts = NULL;
		g_shell.data->path = get_path(envp);
	}
	else
	{
		perror("Error! [failed to init data]\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_shell.exit_status = FALSE;
	g_shell.env = envp_to_list(envp);
	init_data(envp);
	ft_signals();
	ft_prompt(g_shell.data, g_shell.env);
	free_shell();
	restore_termios();
	ft_putstr_fd("exit\n", 1);
	return (0);
}
