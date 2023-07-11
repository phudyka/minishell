/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:06 by kali              #+#    #+#             */
/*   Updated: 2023/07/11 11:38:42 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

char *ft_path(char **envp)
{
    int i;

	i = 0;
    while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
        i++;
    if (!envp[i])
        return (NULL);
    return (ft_strdup(envp[i] + 5));
}

char **get_path(char **envp)
{
    char *path;
    char **final_path;
    int i;

    i = -1;
    path = NULL;
    final_path = NULL;
    path = ft_path(envp);
    if (path == NULL)
        return NULL;
    final_path = ft_split(path, ':');
    free(path);
    while (final_path[++i])
        final_path[i] = ft_strjoin(final_path[i], "/");
    return (final_path); 
}

char **list_to_array(t_env *head)
{
	int		i;
    char	**env; 
    int		count;
    t_env	*current;

	i = 0;
	count = 0;
	current = head;
    while (current)
	{
        count++;
        current = current->next;
    }
	env = (char **)malloc(sizeof(char *) * (count + 1));
    if (!env)
        exit(EXIT_FAILURE);
    current = head;
    while (current)
	{
        env[i] = (char *)malloc((sizeof(char) * ft_strlen(current->var) + 1));
        if (!env[i])
            exit(EXIT_FAILURE);
        ft_strlcpy(env[i], current->var, ft_strlen(current->var));
        current = current->next;
        i++;
    }
    env[i] = NULL;
    return (env);
}

int main(int argc, char **argv, char **envp)
{
	t_data  *data;
	t_env	*env;
	
	(void)argc;
    (void)argv;
    data = NULL;
	env = NULL;
	env = envp_to_list(envp);
    data = malloc(sizeof(t_data));
    data->path = get_path(envp);
	ft_signals();
    ft_prompt(data, env);
	free_list(env);
	free(data);
	ft_putstr_fd("exit\n", 1);
	return (0);
}