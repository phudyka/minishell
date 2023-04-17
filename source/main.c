/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:38:49 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/17 14:53:20 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	main(int argc, char **argv)
{
	(void)argv;

	if (argc == 1)
	{
		size_t	len;
		ssize_t	byte;
		int		state;
		char	*buff;

		len = 0;
		state = 1;
		buff = NULL;
		byte = getline(&buff, &len, stdin);
		while (state)
		{
			state = 0;
			if(byte <= 0 && errno == EINTR) // signal d'nterruption externe au programme
			{
				state = 1;
				clearerr(stdin);
			}
		}
		//system("leaks minishell");
	}
	return (0);   
}
