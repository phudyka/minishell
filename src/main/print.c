/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:08:50 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/24 16:19:18 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

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
