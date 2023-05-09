/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:46:11 by kali              #+#    #+#             */
/*   Updated: 2023/05/09 09:57:01 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

char    *ft_access(char **path, char **cmd)
{
	char	*executable_path;
	char	*current_path;
	int		i;
	int		len;

	i = 0;
	executable_path = NULL;
	while (path[i] != NULL) 
	{
		len = (ft_strlen(path[i]) + ft_strlen(cmd[0]));
		current_path = malloc(sizeof(char) * len + 1);
		if (current_path == NULL) 
			return NULL;
		// Construire le chemin complet
		ft_strlcpy(current_path, path[i], ft_strlen(path[i]) + 1);
		ft_strlcat(current_path, cmd[0], len + 1);
		// Vérifier si le fichier existe et peut être exécuté
        if (access(current_path, F_OK | X_OK) == 0)
		{
			executable_path = current_path;
			break;
		}
        // Libérer la mémoire allouée pour la chaîne de caractères contenant le chemin actuel
        free(current_path);
        i++;
    }
    return (executable_path);
}

static void     exec_cmd(char *path, char **cmd)
{
		pid_t   pid;
		int		status = 0;
		extern char **environ;

		// On fork
		pid = fork();
		if (pid == -1)
			perror("fork");
		// Si le fork a reussit, le processus pere attend l'enfant (process fork)
		else if (pid > 0)
		{
			// On bloque le processus parent jusqu'a ce que l'enfant termine puis
			// On kill le processus enfant
			waitpid(pid, &status, 0);
			kill(pid, SIGTERM);
		}
		else
		{
			// Le processus enfant execute la commande ou exit si execve echoue
			if (execve(path, cmd, environ) == -1)
			{
				printf("%s: Command not found\n", cmd[0]);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
			}
}

void ft_prompt(t_data *data, t_env *env)
{
	// Boucle Prompt avec liberation de memoires
	while ((data->buffer = readline("$ > ")))
	{
		add_history(data->buffer);
		data->cmd = master_parser(data->buffer);
		if (!data->cmd || !data->cmd[0])
		{
			free(data->buffer);
			free(data->cmd);
			continue ;
		}
		if ((is_builtin(data->cmd[0])) == 0)
		{
			exec_builtin(data->cmd, env);
			free_array(data->cmd);
			free (data->buffer);
			continue ;
		}
		else
		{
			free (data->buffer);
			data->buffer = ft_access(data->path, data->cmd);
			exec_cmd(data->buffer, data->cmd);
			free(data->buffer);
			free_array (data->cmd);
		}
	}
	clear_history();
	free_array (data->path);
	free(data->buffer);
	free(data);
}                                