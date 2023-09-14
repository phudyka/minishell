/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:26:28 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/14 08:05:53 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

void	exec_cmd(t_data *data, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error [fork]\n", 2);
		data->error->status = 35;
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (handle_multi_redirections(data) == -1)
			exit(EXIT_FAILURE);
		child_process(data, envp);
	}
	else
		parent_process(data, pid);
}

static void	execute_command(t_data *data, char **envp)
{
	if (data->buffer)
	{
		free(data->buffer);
		data->buffer = NULL;
	}
	if (data->cmd[0][0] == '/')
	{
		if (check_absolute(data))
			return ;
	}
	else
		data->buffer = ft_access(data->path, data->cmd);
	if (!data->buffer && !is_redirection_token(data->cmd[0]))
	{
		if (data->error->status != 1)
		{
			printf("%s : Command not found\n", data->cmd[0]);
			data->error->status = 127;
		}
		return ;
	}
	exec_cmd(data, envp);
}

void	process_command(t_data *data, t_env *env)
{
	char	**envp;

	if (!data->cmd || !data->cmd[0])
	{
		free_buff(data);
		return ;
	}
	if (is_builtin(data) == 0)
	{
		handle_builtin_command(data, env);
		return ;
	}
	envp = list_to_array(env);
	free_array(data->path);
	data->path = get_path(envp);
	execute_command(data, envp);
	free_array(envp);
	free_data(data);
}

static void	master_commander(t_data *data)
{
	int	pipes;

	pipes = 0;
	data->cmd = master_lexer(data);
	if (data->cmd == NULL)
	{
		free_array(data->cmd);
		free(data->buffer);
		return ;
	}
	pipes = count_pipes(data->buffer);
	if (pipes > 0)
		execute_pipeline(data, data->env);
	else
		process_command(data, data->env);
}

void	ft_prompt(t_data *data)
{
	g_signal = 0;
	while (!data->error->exit)
	{
		data->buffer = readline(GREEN "$ > " RESET);
		if (!data->buffer)
			break ;
		if (is_only_spaces_or_tabs(data->buffer))
		{
			free(data->buffer);
			data->buffer = NULL;
			continue ;
		}
		add_history(data->buffer);
		master_commander(data);
	}
	clear_history();
	if (data->path)
		free_array(data->path);
}
