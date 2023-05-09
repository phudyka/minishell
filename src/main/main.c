/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:06 by kali              #+#    #+#             */
/*   Updated: 2023/05/09 11:44:29 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void    free_array(char **tab)
{
	int     i;

	i = 0;
	if (tab[i] == NULL)
		return ;
	while (tab[i])
		i++;
	while (i >= 0)
		free(tab[i--]);
	free (tab);
}

char *ft_path(char **envp)
{
    int i;

	i = 0;
    while (envp[i] && (ft_strncmp(envp[i], "PATH=", 5) != 0))
        i++;
    if (!envp[i])
        return NULL;
    return (ft_strdup(envp[i] + 5));
}

char    **get_path(char **envp)
{
		char	*path;
		char	**final_path;
		int		i;

		i = -1;
		path = NULL;
		final_path = NULL;
		path = ft_path(envp);
		final_path = ft_split(path, ':');
		free (path);
		while (final_path[++i])
			final_path[i] = ft_strjoin(final_path[i], "/");
		return (final_path); 
}

int main(int ac, char **av, char **envp)
{
        t_data  *data;
		t_env	*env;

        (void)ac;
        (void)av;
        data = NULL;
		env = NULL;
		env = envp_to_list(envp);
        // Allocation structure
        data = malloc(sizeof(t_data));
        // Recherche et stockage du PATH=
        data->path = get_path(envp);
        // Lancement du Prompt
		ft_signals();
        ft_prompt(data, env);
        // Fin du Programme
		free_list(env);
		ft_putstr_fd("exit", 1);
        return (0);
}