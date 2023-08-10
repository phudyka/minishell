/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:35:27 by kali              #+#    #+#             */
/*   Updated: 2023/08/10 10:23:07 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

void	execute_builtin_with_redirection(t_data *data, t_env *env)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		ft_putstr_fd("dup", 2);
		g_shell.status = 35;
		return ;
	}
	redirections(data->cmd);
	exec_builtin(data, env);
	if (dup2(saved_stdin, STDIN_FILENO) == -1
		|| dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("dup2", 2);
		g_shell.status = 35;
		return ;
	}
	close(saved_stdin);
	close(saved_stdout);
}

void	child_process(char *path, char **cmd, char **envp)
{
	signal(SIGINT, SIG_DFL);
	redirections(cmd);
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("execve", 2);
		g_shell.status = 127;
	}
}

void	parent_process(pid_t pid)
{
	int	status;

	g_shell.pid = pid;
	if (waitpid(pid, &status, 0) == -1)
	{
		ft_putstr_fd("waitpid", 2);
		g_shell.status = 128;
		exit(EXIT_FAILURE);
	}
	g_shell.pid = 0;
	if (WIFEXITED(status))
		g_shell.status = WEXITSTATUS(status);
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
