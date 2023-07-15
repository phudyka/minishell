/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:43:46 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/15 11:23:39 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

static t_pipe	*init_pipe_data(int i, t_shell *shell)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->data = shell->data;
	pipe->env = shell->env;
	pipe->i = i;
	return (pipe);
}

static void	exec_pipe_child(t_shell *shell)
{
	dup2(shell->pipes->data->fd_in, 0);
	close(shell->pipes->data->fd_in);
	if (shell->pipes->data->cmd_parts[shell->pipes->i + 1])
		dup2(shell->pipes->data->fd[1], 1);
	close(shell->pipes->data->fd[1]);
	close(shell->pipes->data->fd[0]);
	process_command(shell);
	exit(EXIT_SUCCESS);
}

static void	exec_pipe_parent(t_data *data)
{
	wait(NULL);
	close(data->fd[1]);
	data->fd_in = data->fd[0];
}

static void	start_fork(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free_data(shell->data);
		ft_error(PIP, 1, shell);
	}
	else if (pid == 0)
	{
		exec_pipe_child(shell);
		exit(EXIT_FAILURE);
	}
	else
		exec_pipe_parent(shell->data);
}

void	execute_pipeline(t_shell *shell)
{
	int			i;
	t_pipe		*pipe_data;

	shell->data->fd_in = 0;
	i = 0;
	shell->data->cmd_parts = ft_split(shell->data->buffer, '|');
	while (shell->data->cmd_parts[i])
	{
		if (pipe(shell->data->fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		free(shell->data->buffer);
		shell->data->buffer = ft_strdup(shell->data->cmd_parts[i]);
		free_array(shell->data->cmd);
		shell->data->cmd = ft_split(shell->data->buffer, ' ');
		pipe_data = init_pipe_data(i++, shell);
		start_fork(shell);
		free(pipe_data);
	}
	free_data(shell->data);
}
