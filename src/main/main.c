/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:06 by kali              #+#    #+#             */
/*   Updated: 2023/04/20 14:00:37 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void    free_array(char **tab)
{
		int	i;

	i = 0;
	if (tab[i] == NULL)
		return ;
	while (tab[i])
		i++;
	while (i >= 0)
		free(tab[i--]);
	free (tab);
}

char    *ft_path(char **envp)
{
		int             i;
		int             j;
		int             k;
		char    *result;

		i = 0;
		k = 0;
		while (envp[i])
		{
				j = 0;
				if (ft_strnstr(envp[i], "PATH", 4) != 0)
				{
						result = malloc(sizeof(char) * ft_strlen(envp[i]) - 4);
						if (!(result))
								return (NULL);
						j = 5;
						while (envp[i][j])
						{
								result[k++] = envp[i][j++];
						}
						result[k] = '\0';
				}
				i++;
		}
		return (result);
}

char    **get_path(char **envp)
{
	char    *path;
	char    **final_path;
	int		i;

	i = 0;
	path = NULL;
	final_path = NULL;
	path = ft_path(envp);
	final_path = ft_split(path, ':');
	free (path);
	while (final_path[i])
	{
		final_path[i] = ft_strjoin(final_path[i], "/");
		i++;
	}
	return (final_path); 
}

int main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = NULL;
	// Allocation structure
	data = malloc(sizeof(t_data) * 1);
	// Recherche et stockage du PATH=
	data->path = get_path(envp);
	// Lancement du Prompt
	ft_prompt(data);
	// Fin du Programme
	printf("bye\n");
	return (0);
}
