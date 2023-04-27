/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:06 by kali              #+#    #+#             */
/*   Updated: 2023/04/27 14:40:57 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	free_array(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	tab = NULL;
}

char	*ft_path(char **envp)
{
	int		i;
	int		j;
	int		k;
	char	*result;
	
	i = 0;
	k = 0;
	while (envp[i])
	{
		j = 0;
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
		{
			result = malloc(sizeof(char) * ft_strlen(envp[i]) - 4);
			if (!result)
				return (NULL);
			j = 5;
			while (envp[i][j])
				result[k++] = envp[i][j++];
			result[k] = '\0';
		}
		i++;
	}
	return (result);
}

char    **get_path(char **envp)
{
	int		i;
	char	*path;
	char	**final_path;

	i = 0;
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
	data = malloc(sizeof(t_data) * 1);
	data->path = get_path(envp);
	ft_prompt(data);
	printf("exit\n");
	return (0);
}