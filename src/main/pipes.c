/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:43:46 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/11 09:47:27 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/lexer.h"
#include "../../include/parser.h"

// J'initialise la struct t_pipe_data, pas le choix sinon mes fonctions avait
// trop de parametres.

static t_pipe_data	*init_pipe_data(t_data *data, t_env *env, int i)
{
	t_pipe_data	*pipe_data;

	pipe_data = malloc(sizeof(t_pipe_data));
	if (!pipe_data)
		return (NULL);
	pipe_data->data = data;
	pipe_data->env = env;
	pipe_data->i = i;
	return (pipe_data);
}

// Processus fils : il récupère la commande, la fait tourner et se termine.

static void	exec_pipe_child(t_pipe_data *pipe_data)
{
	dup2(pipe_data->data->fd_in, 0);
	close(pipe_data->data->fd_in);
	if (pipe_data->data->cmd_parts[pipe_data->i + 1] != NULL)
		dup2(pipe_data->data->fd[1], 1);
	close(pipe_data->data->fd[1]);
	close(pipe_data->data->fd[0]);
	process_command(pipe_data->data, pipe_data->env);
	exit(EXIT_SUCCESS);
}

// Je ferme la fin d'écriture du pipe et attends qu'il finisse.
static void	exec_pipe_parent(t_data *data)
{
	wait(NULL);
	close(data->fd[1]);
	data->fd_in = data->fd[0];
}

// Je crée un nouveau processus. Si ca foire, je le signale et arrête tout.
static void	start_fork(t_data *data, t_pipe_data *pipe_data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_data(data);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		exec_pipe_child(pipe_data);
		exit(EXIT_FAILURE);
	}
	else
		exec_pipe_parent(data);
}

// Je mets tout en place : créer les pipes, préparer les commandes,
// créer les processus, gérer le processus parent.

void	execute_pipeline(t_data *data, t_env *env)
{
	int			i;
	t_pipe_data	*pipe_data;

	i = 0;
	data->fd_in = 0;
	data->cmd_parts = ft_split(data->buffer, '|');
	while (data->cmd_parts[i])
	{
		if (pipe(data->fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		free(data->buffer);
		data->buffer = ft_strdup(data->cmd_parts[i]);
		free_array(data->cmd);
		data->cmd = ft_split(data->buffer, ' ');
		pipe_data = init_pipe_data(data, env, i++);
		start_fork(data, pipe_data);
		free(pipe_data);
	}
	free_data(data);
}