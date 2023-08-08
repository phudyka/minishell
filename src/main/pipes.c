/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:43:46 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/08 10:35:40 by kali             ###   ########.fr       */
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

static void exec_pipe_child(t_pipe *pipe_data)
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

void execute_pipeline(t_data *data, t_env *env)
{
    int     i;
    t_pipe  *pipe_data;

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

        pipe_data = init_pipe_data(data, env, i);
        
        pid_t pid = fork();
        if (pid == -1)
        {
            free_data(data);
            ft_error(PIP, 1);
        }
        else if (pid == 0)
        {
            exec_pipe_child(pipe_data);
        }
        else
        {
            if (data->fd_in != 0)
                close(data->fd_in);

            close(data->fd[1]);
            data->fd_in = data->fd[0];
        }
        i++;
        free(pipe_data);
    }
    while (wait(NULL) > 0);
    free_data(data);
}