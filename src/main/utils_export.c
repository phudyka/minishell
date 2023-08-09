/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:51:04 by kali              #+#    #+#             */
/*   Updated: 2023/08/09 12:45:11 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	add_new_variable(t_env **env, char *cmd_arg)
{
	t_env	*new_variable;

	new_variable = create_node(cmd_arg);
	add_node(env, new_variable);
}

char	**get_variable(char *cmd_arg)
{
	if (!ft_equal(cmd_arg))
		return (NULL);
	return (ft_split(cmd_arg, '='));
}

int	update_variable_if_exists(t_env *env, char **variable, char *cmd_arg)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->var, variable[0], ft_strlen(variable[0])) == 0)
		{
			free(current->var);
			current->var = strdup(cmd_arg);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	handle_variable(t_data *data, t_env **env)
{
	char	**variable;

	variable = get_variable(data->cmd[1]);
	if (variable)
	{
		if (!update_variable_if_exists(*env, variable, data->cmd[1]))
			add_new_variable(env, data->cmd[1]);
		free_array(variable);
	}
	else
		add_new_variable(env, data->cmd[1]);
}
