/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:43:46 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/29 10:49:15 by kali             ###   ########.fr       */
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
	dup2(pipe_data->data->fd_in, 0);
	close(pipe_data->data->fd_in);
	if (pipe_data->data->cmd_parts[pipe_data->i + 1])
		dup2(pipe_data->data->fd[1], 1);
	close(pipe_data->data->fd[1]);
	close(pipe_data->data->fd[0]);
	process_command(pipe_data->data, pipe_data->env);
	exit(EXIT_SUCCESS);
}

static void	exec_pipe_parent(t_data *data)
{
	wait(NULL);
	close(data->fd[1]);
	data->fd_in = data->fd[0];
}

static void	start_fork(t_data *data, t_pipe *pipe_data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free_data(data);
		ft_error(PIP, 1);
	}
	else if (pid == 0)
	{
		exec_pipe_child(pipe_data);
		exit(EXIT_FAILURE);
	}
	else
		exec_pipe_parent(data);
}

void	execute_pipeline(t_data *data, t_env *env)
{
	int			i;
	t_pipe		*pipe_data;

	i = 0;
	data->fd_in = 0;
	data->cmd_parts = ft_split(data->buffer, '|');
	while (data->cmd_parts[i])
	{
		if (pipe(data->fd) == -1)
			ft_error(PIP, 1);
		free(data->buffer);
		data->buffer = ft_strdup(data->cmd_parts[i]);
		free_array(data->cmd);
		data->cmd = ft_split(data->buffer, ' ');
		pipe_data = init_pipe_data(data, env, i++);
		start_fork(data, pipe_data);
		free(pipe_data);
	}
	free_data(data);
}