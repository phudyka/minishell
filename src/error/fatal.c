/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:55:07 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/14 15:29:08 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/error.h"

void	fatal_error(int code, t_shell *shell)
{
	if (code == 1)
		perror("FATAL ERROR ! [fork]\n");
	else if (code == 2)
		perror("FATAL ERROR ! [execve]\n");
	else if (code == 3)
		perror("FATAL ERROR ! [waitpid]\n");
	ft_freeshell(shell);
	exit (EXIT_FAILURE);
}
