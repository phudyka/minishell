/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:07:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/04 21:01:34 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

t_env	*create_node(char *var)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node)
	{
		node->var = ft_strdup(var);
		node->next = NULL;
	}
	else
	{
		perror("malloc");
		return(NULL);
	}
	return (node);
}

void	add_node(t_env **head, t_env *node)
{
	t_env	*current;

	if (!*head)
		*head = node;
	else 
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

void	unset_list(t_env **env, char *var)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *env;
	while (current && ft_strncmp(current->var, var, ft_strlen(var)) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	if (!prev)
		*env = current->next;
	else
		prev->next = current->next;
	free (current->var);
	current->var = NULL;
	free (current);
	current = NULL;
}