/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:26:28 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 15:29:52 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

void execute_builtin_with_redirection(t_data *data, t_env *env)
{
    int saved_stdin;
    int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdin == -1 || saved_stdout == -1)
    {
        perror("dup");
        return;
    }
    redirections(data->cmd);
    exec_builtin(data, env);
    if (dup2(saved_stdin, STDIN_FILENO) == -1 || dup2(saved_stdout, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        return;
    }
    close(saved_stdin);
    close(saved_stdout);
}

int	count_pipes(char *str)
{
	int pipes;
	int i;
	char q;

	pipes = 0;
	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (!q)
				q = str[i];
			else if (q == str[i])
				q = 0;
		}
		else if (!q && str[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
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
			return(NULL);
		if (access(exe, F_OK | X_OK) == 0)
			return (exe);
		free(exe);
		i++;
	}
	return (NULL);
}

void exec_cmd(char *path, char **cmd, char **envp)
{
    pid_t pid;
    int status;

    if (!path)
    {
        printf("%s: Command not found\n", cmd[0]);
        g_shell.status = 1;
        return ;
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        redirections(cmd);
        if (execve(path, cmd, envp) == -1)
            perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        g_shell.pid = pid;
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        g_shell.pid = 0;
        if (WIFEXITED(status))
            g_shell.status = WEXITSTATUS(status);
    }
}

static void	execute_command(t_data *data, char **envp)
{
    if (data->buffer)
    {
        free(data->buffer);
        data->buffer = NULL;
    }
    if (data->cmd[0][0] == '/')
        data->buffer = ft_strdup(data->cmd[0]);
    else
        data->buffer = ft_access(data->path, data->cmd);
    exec_cmd(data->buffer, data->cmd, envp);
}

void process_command(t_data *data, t_env *env)
{
    char **envp;

    envp = list_to_array(env);
    free_array(data->path);
    data->path = get_path(envp);
    if (!data->cmd || !data->cmd[0])
    {
        free_array(envp);
        free_buff(data);
        return ;
    }
    if (is_builtin(data) == 0)
    {
        execute_builtin_with_redirection(data, env);
		free_array(envp);
		free_data(data);
        return ;
    }
    execute_command(data, envp);
    free_array(envp);
    free_data(data);
}

void	ft_prompt(t_data *data, t_env *env)
{
	int	pipes;

	pipes = 0;
	g_shell.pid = 0;
    g_shell.status = 0;
	while (69)
	{
		data->buffer = readline(GREEN "$ > " RESET);
		if (!data->buffer)
			break ;
		add_history(data->buffer);
		data->cmd = master_lexer(data->buffer);
		pipes = count_pipes(data->buffer);
		if (pipes > 0)
			execute_pipeline(data, env);
		else
			process_command(data, env);
	}
	clear_history();
	if (data->path)
		free_array(data->path);
}