/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:06 by kali              #+#    #+#             */
/*   Updated: 2023/07/29 11:52:42 by kali             ###   ########.fr       */
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

static char	**make_env(char **env, t_env *current)
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

char	**list_to_array(t_env *head)
{
	int		count;
	char	**env;
	t_env	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	env = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!env)
		exit(EXIT_FAILURE);
	current = head;
	env = make_env(env, current);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_shell.env = envp_to_list(envp);
	g_shell.data = malloc(sizeof(t_data));
	if (g_shell.data != NULL)
	{
    	g_shell.data->buffer = NULL;
    	g_shell.data->cmd = NULL;
    	g_shell.data->cmd_parts = NULL;
	}
    g_shell.data->path = get_path(envp);
	ft_signals();
	ft_prompt(g_shell.data, g_shell.env);
	free_shell();
	ft_putstr_fd("exit\n", 1);
	return (0);
}
