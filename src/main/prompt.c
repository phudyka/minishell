/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:46:11 by kali              #+#    #+#             */
/*   Updated: 2023/05/05 11:29:32 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

char	*ft_access(char **path, char **cmd)
{
	int		i;
	char	*exec;

	if (!path || !*path || !cmd || !*cmd)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		if ((exec = ft_strjoin(ft_strjoin(path[i], "/"), cmd[0])) &&
			!access(exec, F_OK | X_OK))
			return (exec);
	}
	return (NULL);
}

static void exec_cmd(char *path, char **cmd)
{
	pid_t		pid;
	int			status;
	extern char **environ;	

	pid = fork();
	status = 0;
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(path, cmd, environ) == -1)
		{
			printf("%s: Command not found\n", cmd[0]);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}

static void	ft_free(char *temp, char **cmd)
{
	if (cmd)
		exec_builtin(cmd);
	free(temp);
	temp = NULL;
}

void ft_prompt(t_data *data)
{
	while ((data->buffer = readline("$ > ")))
	{
		if (!data->buffer || !data->buffer[0])
			continue;
		add_history(data->buffer);
		data->cmd = master_parser(data->buffer);
		if (!data->cmd || !data->cmd[0])
		{
			ft_free(data->buffer, NULL);
			continue ;
		}
		if ((is_builtin(data->cmd[0])) == 0)
		{
			ft_free(data->buffer, data->cmd);
			continue ;
		}
		else
		{
			data->buffer = ft_access(data->path, data->cmd);
			exec_cmd(data->buffer, data->cmd);
		}
	}
	clear_history();
}