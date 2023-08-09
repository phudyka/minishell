/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:10:27 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 22:47:29 by phudyka          ###   ########.fr       */
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

void	free_data(t_data *data)
{
	free(data->buffer);
	free_array(data->cmd);
	free_array(data->cmd_parts);
	data->buffer = NULL;
	data->cmd = NULL;
	data->cmd_parts = NULL;
}

void	free_shell(void)
{
	if (g_shell.env)
	{
		free_env(g_shell.env);
		g_shell.env = NULL;
	}
	if (g_shell.data)
	{
		free_data(g_shell.data);
		g_shell.data = NULL;
	}
	if (g_shell.tokens)
	{
		free_tokens(g_shell.tokens);
		g_shell.tokens = NULL;
	}
}

void	builtin_exit(void)
{
	free_shell();
	exit (g_shell.exit_status = TRUE);
}
