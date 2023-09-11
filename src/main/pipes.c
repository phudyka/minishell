/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:43:46 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/11 11:13:31 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

t_pipe	*init_pipe_data(t_data *data, t_env *env, int i)
{
	t_pipe	*pipe_data;

	pipe_data = malloc(sizeof(t_pipe));
	if (!pipe_data)
		return (NULL);
	pipe_data->data = data;
	pipe_data->env = env;
	pipe_data->i = i;
	return (pipe_data);
}

void	exec_pipe_child(t_pipe *pipe_data)
{
	if (pipe_data->i > 0)
		dup2(pipe_data->data->fd_in, 0);
	if (pipe_data->data->cmd_parts[pipe_data->i + 1])
		dup2(pipe_data->data->fd[1], 1);
	close(pipe_data->data->fd[0]);
	close(pipe_data->data->fd[1]);
	if (pipe_data->data->fd_in != 0)
		close(pipe_data->data->fd_in);
	if (is_builtin(pipe_data->data) == 0)
	{
		execute_builtin_with_redirection(pipe_data->data, pipe_data->env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		process_command(pipe_data->data, pipe_data->env);
		exit(EXIT_SUCCESS);
	}
}

void	handle_parent_process(t_data *data)
{
	if (data->fd_in != 0)
		close(data->fd_in);
	close(data->fd[1]);
	data->fd_in = data->fd[0];
}

static void	execute_commands(t_data *data, t_env *env)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	while (data->cmd_parts[i])
	{
		handle_pipe_execution(data, env, i);
		i++;
	}
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
		pid = waitpid(-1, &status, 0);
}

void	execute_pipeline(t_data *data, t_env *env)
{
	signal(SIGPIPE, SIG_IGN);
	data->fd_in = 0;
	data->cmd_parts = group_by_pipes(data->cmd);
	if (data->cmd_parts[0] && !data->cmd_parts[1])
		read_next_command(data);
	execute_commands(data, env);
	free_data(data);
}
