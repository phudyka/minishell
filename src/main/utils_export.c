/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:51:04 by kali              #+#    #+#             */
/*   Updated: 2023/09/14 11:34:49 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	add_new_variable(t_data *data, t_env **env, char *cmd_arg)
{
	t_env	*new_variable;

	new_variable = create_node(data, cmd_arg);
	add_node(env, new_variable);
}

char	**get_variable(char *cmd_arg)
{
	if (!ft_equal(cmd_arg))
		return (NULL);
	return (ft_split(cmd_arg, '='));
}

int	update_var(t_data *data, t_env *env, char **variable, char *cmd_arg)
{
	t_env	*current;

	if (!variable || !variable[0] || !cmd_arg)
	{
		printf("bash: export: `%s': not a valid identifier\n", data->cmd[1]);
		data->error->status = 1;
		return (0);
	}
	current = env;
	while (current)
	{
		if (ft_strncmp(current->var, variable[0], ft_strlen(variable[0])) == 0)
		{
			free(current->var);
			current->var = ft_strdup(cmd_arg);
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
		if (*env)
		{
			if (!update_var(data, *env, variable, data->cmd[1]))
				add_new_variable(data, env, data->cmd[1]);
			free_array(variable);
		}
		else
			add_new_variable(data, env, data->cmd[1]);
	}
	else
		return ;
}
