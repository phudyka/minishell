/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:43:46 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/16 02:23:52 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

static t_pipe	*init_pipe_data(t_data *data, t_env *env, int i)
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

static void	exec_pipe_child(t_pipe *pipe_data)
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
		execute_builtin_with_redirection(pipe_data->data, pipe_data->env);
	else
		process_command(pipe_data->data, pipe_data->env);
	exit(EXIT_SUCCESS);
}

static void	handle_parent_process(t_data *data)
{
	if (data->fd_in != 0)
		close(data->fd_in);
	close(data->fd[1]);
	data->fd_in = data->fd[0];
}

static void	handle_pipe_execution(t_data *data, t_env *env, int i)
{
	pid_t	pid;
	t_pipe	*pipe_data;

	if (pipe(data->fd) == -1)
		ft_error(PIP, 1);
	free(data->buffer);
	data->buffer = ft_strdup(data->cmd_parts[i]);
	free_array(data->cmd);
	data->cmd = ft_split(data->buffer, ' ');
	pipe_data = init_pipe_data(data, env, i);
	pid = fork();
	if (pid == -1 || pid == 0)
	{
		if (pid == -1)
			free_data(data);
		if (pid == 0)
			exec_pipe_child(pipe_data);
		ft_error(PIP, 1);
	}
	handle_parent_process(data);
	free(pipe_data);
}

void	execute_pipeline(t_data *data, t_env *env)
{
	int		i;
	int		status;
	pid_t	pid;

	data->fd_in = 0;
	data->cmd_parts = ft_split(data->buffer, '|');
	i = 0;
	while (data->cmd_parts[i])
	{
		if (is_exit_command(data->cmd_parts[i]))
		{
			//g_shell.exit_status = TRUE;
			free_data(data);
			return ;
		}
		handle_pipe_execution(data, env, i);
		i++;
	}
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
		pid = waitpid(-1, &status, 0);
	free_data(data);
}
