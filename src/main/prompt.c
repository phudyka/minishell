/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:46:11 by kali              #+#    #+#             */
/*   Updated: 2023/04/27 14:31:51 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

char	*ft_access(char **path, char **cmd)
{
	int i;
	int len;
	char *executable_path;
	char *current_path;

	i = 0;
	executable_path = NULL;
	while (path[i])
	{
		len = (ft_strlen(path[i]) + ft_strlen(cmd[0]));
		current_path = malloc(sizeof(char) * len + 1);
		if (!current_path)
			return NULL;
		ft_strlcpy(current_path, path[i], ft_strlen(path[i]) + 1);
		ft_strlcat(current_path, cmd[0], len + 1);
		if (access(current_path, F_OK | X_OK) == 0)
		{
			executable_path = current_path;
			break;
		}
		i++;
	}
	return (executable_path);
}

static void exec_cmd(char *path, char **cmd)
{
	pid_t pid;
	int status;

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
		printf("%s\n", path);
		if (execve(path, cmd, NULL) == -1)
		{
			printf("%s: Command not found\n", cmd[0]);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}

void ft_prompt(t_data *data)
{
	while ((data->buffer = readline("$ > ")))
	{
		if (!data->buffer || !data->buffer[0])
			continue;
		//ft_signals(); -> probleme d'include
		add_history(data->buffer);
		data->cmd = master_parser(data->buffer);
		if (!data->cmd || !data->cmd[0])
		{
    		//free(data->buffer);
    		continue ;
		}
		if ((is_builtin(data->cmd[0])) == 0)
		{
			exec_builtin(data->cmd);
			//free_array(data->cmd);
			//free (data->buffer);
			continue ;
		}
		else
		{
			data->buffer = ft_access(data->path, data->cmd);
			exec_cmd(data->buffer, data->cmd);
			//free_array (data->cmd);
		}
	}
	clear_history();
	//free_array(data->path);
}