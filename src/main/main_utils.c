/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:25:15 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/04 14:42:30 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	free_tab(char *tab)
{
	if (!tab)
		return. ;
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
		return ;
	while(*tab)
	{
		free(*tab);
		tab++;
	}
	*tab = NULL;	
}

void	ft_free(t_data *data)
{
	if (!data)
		return ;
	if ()
	while(data->next)
	{
		free(data);
		data++;
	}
	data = NULL;
}