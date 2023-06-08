/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:26:28 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/08 10:09:09 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/lexer.h"
#include "../../include/parser.h"

char	*ft_access(char **path, char **cmd)
{
	int     i;
	int     len;
	char    *exec;
	char    *cur;
	
	i = 0;
	exec = NULL;
	while (path[i]) 
	{
                len = (ft_strlen(path[i]) + ft_strlen(cmd[0]));
		cur = malloc(sizeof(char) * len + 1);
		if (!cur)
			return (NULL);
		// Construire le chemin complet
		ft_strlcpy(cur, path[i], ft_strlen(path[i]) + 1);
		ft_strlcat(cur, cmd[0], len + 1);
		// Vérifier si le fichier existe et peut être exécuté
		if (access(cur, F_OK | X_OK) == 0)
		{
			exec = cur;
			break;
		}
        // Libérer la mémoire allouée pour la chaîne de caractères contenant le chemin actuel
        free(cur);
        i++;
    }
    return (exec);
}

static void	exec_cmd(char *path, char **cmd)
{
	pid_t	pid;
	int		status;  
	
	// On fork
	status = 0;
	pid = fork();
	if (pid == -1)
		perror("Error! [Failed to fork]\n");
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
		if (execve(path, cmd, NULL) == -1)
		{
			printf("%s: Command not found\n", cmd[0]);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}

void	ft_prompt(t_data *data, t_env *env)
{
	while ((data->buffer = readline(GREEN "$ > " RESET)))
	{
		add_history(data->buffer);
		data->cmd = master_lexer(data->buffer);
		if (!data->cmd || !data->cmd[0])
		{
			free(data->buffer);
			free(data->cmd);
			continue ;
		}
		if ((is_builtin(data)) == 0)
		{
			exec_builtin(data, env);
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