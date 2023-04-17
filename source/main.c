/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:38:49 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/17 09:21:41 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
    {
		while (shell_ok())
		{
			if(readline(parser(argc, argv)))
			{
				return(ft_error(A_KO));
				return (0);
			}
		}
	}
	return (0);   
}
