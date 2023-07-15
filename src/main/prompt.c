/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:26:28 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/15 11:21:47 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

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

static void	process_pid(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_error(FATAL, 1, shell);
	else if (pid == 0)
		ft_error(FATAL, 2, shell);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			ft_error(FATAL, 3, shell);
	}
}

void	execute_command(t_shell *shell)
{
	t_data	*data;
	
	data = shell->data;
	if (!data->path)
	{
		printf("%s : Commande introuvable\n", data->cmd[0]);
		return ;
	}
	if (data->buffer)
	{
		free(data->buffer);
		data->buffer = NULL;
	}
	data->buffer = ft_access(data->path, data->cmd);
	process_pid(shell);
}

void	process_command(t_shell *shell)
{
	char	**envp;

	envp = list_to_array(shell->env);
	if (shell->data->path) 
	{
		free_array(shell->data->path);
		shell->data->path = get_path(envp);
	}
	if (!shell->data->cmd || !shell->data->cmd[0])
	{
		free_buff(shell->data);
		return ;
	}
	if (is_builtin(shell) == 0)
	{
		exec_builtin(shell);
		free_buff(shell->data);
		return ;
	}
	execute_command(shell);
	free_array(envp);
	free_buff(shell->data);
}

void	ft_prompt(t_shell *shell)
{
	int		pipes;
	char	*buff;

	pipes = 0;
	buff = shell->data->buffer;
	while (69)
	{
		buff = readline(GREEN "$ > " RESET);
		if (!buff)
			break ;
		add_history(buff);
		shell->data->cmd = master_lexer(buff, shell);
		pipes = find_pipes(shell->data);
		if (pipes > 0)
			execute_pipeline(shell);
		else
			process_command(shell);
	}
	clear_history();
	if (shell->data->path)
		free_array(shell->data->path);
}
