/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 05:46:11 by kali              #+#    #+#             */
/*   Updated: 2023/04/21 11:08:33 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

char	*ft_access(char **path, char **cmd)
{
	int		i;
	int		len;
    char	*executable_path;
    char	*current_path;

	i = 0;
	executable_path = NULL;
    while (path[i] != NULL) 
	{
		len = (ft_strlen(path[i]) + ft_strlen(cmd[0]));
        current_path = malloc(sizeof(char) * len + 1);
        if (!current_path) 
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

static void	exec_cmd(char *path, char **cmd)
{
	pid_t	pid = 0;
	int		status = 0;

	// On fork
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0)
	{
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant :'(
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		// Le processus enfant execute la commande ou exit si execve echoue
		if (execve(path, cmd, NULL) == -1)
		{
			printf("Command not found\n");
			exit(EXIT_FAILURE);
			}
		exit(EXIT_SUCCESS);
	}
}

void ft_prompt(t_data *data)
{
    // Boucle Prompt avec liberation de memoires
    while ((data->buffer = readline("$ > ")))
	{
		data->cmd = ft_parse(data->buffer);
		if (!data->cmd || !data->cmd[0])
		{
    		free(data->buffer);
    		continue;
		}
		free (data->buffer);
		data->buffer = ft_access(data->path, data->cmd);
		exec_cmd(data->buffer, data->cmd);
		free(data->buffer);
		free_array (data->cmd);
	}
	free_array (data->path);
	free(data->buffer);
	free(data);
}
