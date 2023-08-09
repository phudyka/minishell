/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:26:28 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 11:47:15 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

int	count_pipes(char *str)
{
	int		pipes;
	int		i;
	char	q;

	pipes = 0;
	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!q)
				q = str[i];
			else if (q == str[i])
				q = 0;
		}
		else if (!q && str[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

void	exec_cmd(char *path, char **cmd, char **envp)
{
	pid_t	pid;

	check_path_and_set_status(path, cmd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process(path, cmd, envp);
	else
		parent_process(pid);
}

static void	execute_command(t_data *data, char **envp)
{
	if (data->buffer)
	{
		free(data->buffer);
		data->buffer = NULL;
	}
	if (data->cmd[0][0] == '/')
		data->buffer = ft_strdup(data->cmd[0]);
	else
		data->buffer = ft_access(data->path, data->cmd);
	exec_cmd(data->buffer, data->cmd, envp);
}

void	process_command(t_data *data, t_env *env)
{
	char	**envp;

	envp = list_to_array(env);
	free_array(data->path);
	data->path = get_path(envp);
	if (!data->cmd || !data->cmd[0])
	{
		free_array(envp);
		free_buff(data);
		return ;
	}
	if (is_builtin(data) == 0)
	{
		execute_builtin_with_redirection(data, env);
		free_array(envp);
		free_data(data);
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
	g_shell.pid = 0;
	g_shell.status = 0;
	while (69)
	{
		data->buffer = readline(GREEN "$ > " RESET);
		if (!data->buffer)
			break ;
		add_history(data->buffer);
		data->cmd = master_lexer(data->buffer);
		pipes = count_pipes(data->buffer);
		if (ft_strcmp(data->cmd[0], "exit") == 0)
			builtin_exit();
		if (pipes > 0)
			execute_pipeline(data, env);
		else
			process_command(data, env);
	}
	clear_history();
	if (data->path)
		free_array(data->path);
}
