/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:19:22 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/06 15:24:46 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/expander.h"

void	master_expander(char meta, const char *str)
{
	if (meta == '$')
		ft_dollar(str);	
}