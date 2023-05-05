/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:24:41 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/05 10:54:20 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	free_tab(char *tab)
{
	if (!*tab)
		return;
	while(*tab)
	{
		free(tab);
		tab++;
	}
	tab = NULL;
}

void	free_ttab(char **tab)
{
	if (!*tab)
		return;
	while(*tab)
	{
		free(*tab);
		tab++;
	}
	*tab = NULL;		
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	while(data->next)
	{
		free(data);
		data++;
	}
	data = NULL;
}
