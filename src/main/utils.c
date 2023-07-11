/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:18:00 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/11 10:35:08 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

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

void    free_array(char **tab)
{
	int i;

	i = 0;
	if (!tab[i])
		return ;
	while (tab[i])
		i++;
	while (i >= 0)
		free(tab[i--]);
	free (tab);
}

void	free_data(t_data *data)
{
	free(data->buffer);
	free_array(data->cmd);
	free_array(data->cmd_parts);
	data->buffer = NULL;
	data->cmd = NULL;
	data->cmd_parts = NULL;
}