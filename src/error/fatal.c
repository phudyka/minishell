/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:55:07 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/09 11:56:02 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/error.h"

void	fatal_error(int code)
{
	if (code == 0)
		ft_putstr_fd("FATAL ERROR ! [Causing minishell to stop]\n", 2);
}