/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:10:27 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 03:39:33 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	is_exit_command(char *cmd_part)
{
	int	j;

	j = 0;
	while (cmd_part[j] && (cmd_part[j] == ' ' || cmd_part[j] == '\t'))
		j++;
	return (!ft_strncmp(cmd_part + j, "exit", 4));
}

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
	g_shell.exit_status = TRUE;
}
