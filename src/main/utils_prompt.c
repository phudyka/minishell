/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:35:27 by kali              #+#    #+#             */
/*   Updated: 2023/08/31 11:51:40 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

int	is_only_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	execute_builtin_with_redirection(t_data *data, t_env *env)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		ft_putstr_fd("Error! [dup]\n", 2);
		data->error->status = 1;
		return ;
	}
	redirections(data, data->cmd);
	exec_builtin(data, env);
	if (dup2(saved_stdin, STDIN_FILENO) == -1
		|| dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error! [dup2]\n", 2);
		data->error->status = 1;
		return ;
	}
	close(saved_stdin);
	close(saved_stdout);
}

void	child_process(t_data *data, char **envp)
{
	signal(SIGINT, SIG_DFL);
	redirections(data, data->cmd);
	if (execve(data->buffer, data->cmd, envp) == -1)
	{
		printf("%s : Command not found\n", data->cmd[0]);
		data->error->status = 127;
		exit(EXIT_FAILURE);
	}
}

void	parent_process(t_data *data, pid_t pid)
{
	int	status;

	g_signal = pid;
	if (waitpid(pid, &status, 0) == -1)
	{
		ft_putstr_fd("Error [waitpid]\n", 2);
		data->error->status = 128;
		exit(EXIT_FAILURE);
	}
	g_signal = 0;
	if (WIFEXITED(status))
		data->error->status = WEXITSTATUS(status);
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
			return (NULL);
		if (access(exe, F_OK | X_OK) == 0)
			return (exe);
		free(exe);
		i++;
	}
	return (NULL);
}
