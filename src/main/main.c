/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:06 by kali              #+#    #+#             */
/*   Updated: 2023/05/30 14:33:31 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void    free_array(char **tab)
{
	int	i;

	i = 0;
	if (!tab[i])
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
	int		i;
	char	*path;
	char	**final_path;

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
	t_env	*env;
    t_data  *data;
	
	(void)ac;
	(void)av;
	data = NULL;
	env = NULL;
	env = envp_to_list(envp);
    data = malloc(sizeof(t_data));
    data->path = get_path(envp);
	ft_signals();
	ft_prompt(data, env);
	free_list(env);
	ft_putstr_fd("exit", 1);
	return (0);
}