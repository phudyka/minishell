/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:35:27 by kali              #+#    #+#             */
/*   Updated: 2023/09/14 08:06:09 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

void	handle_builtin_command(t_data *data, t_env *env)
{
	char	**envp;
	int		original_stdout;

	envp = list_to_array(env);
	original_stdout = dup(STDOUT_FILENO);
	if (handle_multi_redirections(data) == -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
		free_array(envp);
		free_data(data);
		return ;
	}
	exec_builtin(data, env);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	free_array(envp);
	free_data(data);
}

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

void	child_process(t_data *data, char **envp)
{
	signal(SIGINT, SIG_DFL);
	handle_multi_redirections(data);
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
