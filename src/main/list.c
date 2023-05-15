/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:07:20 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/15 18:07:20 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

void    free_list(t_env *env)
{
        t_env   *tmp;

        while (env != NULL)
        {
                tmp = env;
                env = env->next;
                free (tmp->var);
                free (tmp);
        }
}

void unset_list(t_env **env, char *var)
{
        t_env *current;
        t_env *prev;

        current = *env;
        prev = NULL;
        while (current != NULL
                && ft_strncmp(current->var, var, ft_strlen(var)) != 0) 
        {
                prev = current;
                current = current->next;
        }
        if (current == NULL)
                return;
        if (prev == NULL)
                *env = current->next;
        else
                prev->next = current->next;

        free(current->var);
        free(current);
}

void    print_list(t_env *env)
{
        t_env   *tmp;

        tmp = env;
        while (tmp)
        {
                printf("%s\n", tmp->var);
                tmp = tmp->next;
        }
}

t_env *create_node(char *var)
{
        t_env *node;

        node = malloc(sizeof(t_env));
        if (node)
        {
                node->var = ft_strdup(var);
                node->next = NULL;
        }
        return (node);
}

void add_node(t_env **head, t_env *node)
{
        if (*head == NULL) 
                *head = node;
        else 
        {
                t_env *current = *head;
                while (current->next != NULL)
                        current = current->next;
                current->next = node;
        }
}