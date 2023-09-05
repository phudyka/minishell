/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:43:46 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/05 11:28:35 by kali             ###   ########.fr       */
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

static void	handle_parent_process(t_data *data)
{
	if (data->fd_in != 0)
		close(data->fd_in);
	close(data->fd[1]);
	data->fd_in = data->fd[0];
}

char	*read_line(void)
{
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	getline(&line, &len, stdin);
	return (line);
}

static void	handle_pipe_execution(t_data *data, t_env *env, int i)
{
	pid_t	pid;
	t_pipe	*pipe_data;

	if (pipe(data->fd) == -1)
		ft_error(data->error, PIP, 0);
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
		ft_error(data->error, PIP, 0);
	}
	handle_parent_process(data);
	free(pipe_data);
}

static int	count_cmd_parts(char **cmd_parts)
{
	int	i;

	i = 0;
	while (cmd_parts && cmd_parts[i])
		i++;
	return (i);
}

char	**add_command_to_cmd_parts(char **cmd_parts, char *new_command)
{
	int		i;
	char	**new_cmd_parts;

	i = count_cmd_parts(cmd_parts);
	new_cmd_parts = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_cmd_parts)
		return (NULL);
	i = 0;
	while (cmd_parts && cmd_parts[i])
	{
		new_cmd_parts[i] = cmd_parts[i];
		i++;
	}
	new_cmd_parts[i] = ft_strdup(new_command);
	new_cmd_parts[i + 1] = NULL;
	free(cmd_parts);
	return (new_cmd_parts);
}

static void	read_next_command(t_data *data)
{
	char	*next_command;
	size_t	len;
	ssize_t	nread;

	next_command = NULL;
	len = 0;
	printf("> ");
	nread = getline(&next_command, &len, stdin);
	if (nread > 0)
	{
		if (next_command[nread - 1] == '\n')
			next_command[nread - 1] = '\0';
		data->cmd_parts = add_command_to_cmd_parts(data->cmd_parts, next_command);
	}
	free(next_command);
}

static void	execute_commands(t_data *data, t_env *env)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	while (data->cmd_parts[i])
	{
		if (is_exit_command(data->cmd_parts[i]))
		{
			data->error->exit = TRUE;
			free_data(data);
			return ;
		}
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
