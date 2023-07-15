/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:11:55 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/15 11:51:47 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ft_freeshell(t_shell *shell)
{
	if (shell->data)
		free_data(shell->data);
	if (shell->env)
		free_list(shell->env);
    if (shell->tokens)
        free_token(shell->tokens);
	shell->env = NULL;
	shell->data = NULL;
    shell->tokens = NULL;
}

void	builtin_exit(t_shell *shell)
{
	free_shell(shell);
    exit (EXIT_SUCCESS);
}
