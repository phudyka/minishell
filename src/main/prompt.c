/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:26:28 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/28 11:50:57 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

int	find_pipes(t_data *data)
{
	int i;
	int pipes;

	i = 0;
	pipes = 0;
	if (!data->buffer || !data->cmd || !*data->cmd)
		return (0);
	while (data->cmd[i])
	{
		if (ft_strncmp(data->cmd[i], "|", ft_strlen(data->cmd[i])) == 0)
			pipes++;
		i++;
	}
	return (pipes);
}

char	*ft_access(char **path, char **cmd)
{
	int		i;
	char	*exe;

	i = 0;
	if (!path || !path[0])
		return (NULL);
	while (path[i])
	{
		exe = allocatenate(cmd[0], path[i]);
		if (!exe)
			return(NULL);
		if (access(exe, F_OK | X_OK) == 0)
			return (exe);
		free(exe);
		i++;
	}
	return (NULL);
}

void	exec_cmd(char *path, char **cmd, char **envp)
{
	pid_t	pid;
	int		status;

	if (!path)
	{
		printf("%s: Command not found\n", cmd[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(path, cmd, envp) == -1)
			perror("execve");
		exit (EXIT_FAILURE);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
}

static void	execute_command(t_data *data, char **envp)
{
    if (data->buffer)
    {
        free(data->buffer);
        data->buffer = NULL;
    }
    data->buffer = ft_access(data->path, data->cmd);
    exec_cmd(data->buffer, data->cmd, envp);
}

void	process_command(t_data *data, t_env *env)
{
	char	**envp;

	envp = list_to_array(env);
	if (data->path)
	{
		free_array(data->path);
		data->path = get_path(envp);
	}
	if (!data->cmd || !data->cmd[0])
	{
		free_array(envp);
		free_buff(data);
		return ;
	}
	if (is_builtin(data) == 0)
	{
		exec_builtin(data, env);
		free_array(envp);
		free_buff(data);
		return ;
	}
	execute_command(data, envp);
	free_array(envp);
	free_data(data);
}

void	ft_prompt(t_data *data, t_env *env)
{
	int	pipes;

	pipes = 0;
	while (69)
	{
		data->buffer = readline(GREEN "$ > " RESET);
		if (!data->buffer)
			break ;
		add_history(data->buffer);
		data->cmd = master_lexer(data->buffer);
		pipes = find_pipes(data);
		if (pipes > 0)
			execute_pipeline(data, env);
		else
			process_command(data, env);
	}
	clear_history();
	free_array(data->path);
}
