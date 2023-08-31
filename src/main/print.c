/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:08:50 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/31 12:01:08 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int	check_absolute(t_data *data)
{
	if (!ft_isalpha(data->cmd[0][1]))
	{
		printf("/: Is a directory\n");
		data->error->status = 126;
		return (1);
	}
	if (access(data->cmd[0], F_OK | X_OK) == -1)
	{
		printf("%s : No such file or directory\n", data->cmd[0]);
		data->error->status = 127;
		return (1);
	}
	data->buffer = ft_strdup(data->cmd[0]);
	return (0);
}

void	print_list_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	print_list(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	print_arguments(t_data *data, int start_index)
{
	int		i;
	size_t	arg_len;

	i = start_index;
	while (data->cmd[i])
	{
		arg_len = ft_strlen(data->cmd[i]);
		write(1, data->cmd[i], arg_len);
		i++;
		if (data->cmd[i])
			write(1, " ", 1);
	}
	data->error->status = 0;
}
