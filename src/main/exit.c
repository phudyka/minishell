/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:10:27 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/18 15:18:15 phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free (tmp->var);
		free (tmp);
	}
}

void	free_shell(void)
{
	if (g_shell.env)
		free_env(g_shell.env);
	if (g_shell.data)
		free_data(g_shell.data);
	if (g_shell.tokens)
		free_tokens(g_shell.tokens);
}

void	builtin_exit(void)
{
	free_shell();
	exit (EXIT_SUCCESS);
}