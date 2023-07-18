/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:19:38 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/13 09:25:04 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

t_env	*envp_to_list(char **envp)
{
	int		i;
	t_env	*head;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		add_node(&head, create_node(envp[i]));
		i++;
	}
	return (head);
}

char	*get_from_env(char *variable, t_env *env)
{
	char	*str;
	char	**tmp;
	t_env	*current;

	tmp = NULL;
	str = NULL;
	current = env;
	while (current)
	{
		if (ft_strncmp(current->var,
				variable, ft_strlen(variable)) == 0)
		{
			tmp = ft_split(current->var, '=');
			str = ft_strdup(tmp[1]);
			free_array(tmp);
			return (str);
		}
		current = current->next;
	}
	return (NULL);
}

int	search_in_env(t_env *env, char *variable)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->var, variable,
				ft_strlen(variable)) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}
