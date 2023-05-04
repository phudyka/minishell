/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:06 by kali              #+#    #+#             */
/*   Updated: 2023/05/04 14:55:12 by phudyka          ###   ########.fr       */
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
        return NULL;
    return (ft_strdup(envp[i] + 5));
}

char **get_path(char **envp)
{
    int i;
    char *path;
    char **final_path;

	i = -1;
	path = ft_path(envp);
	final_path = ft_split(path, ':');
    while (final_path[++i])
        final_path[i] = ft_strjoin(final_path[i], "/");
    free(path);
    return (final_path);
}

t_data	*ft_init_data(char **envp)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->path = get_path(envp);
	return(data);
}

int main(int ac, char **av, char **envp)
{
	t_data *data;

	(void)ac;
	(void)av;
	data = ft_init_data(envp);
	ft_signals();
	ft_prompt(data);
    ft_putstr_fd("exit\n", 1);
	//system("leaks ./minishell");
	return (0);
}