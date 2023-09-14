/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:22:05 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/14 10:17:19 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static int	ft_ischar(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	no_exit(char **split, t_data *data)
{
	printf("exit\nbash: exit: too many arguments\n");
	free_array(split);
	split = NULL;
	data->error->status = 1;
	data->error->exit = FALSE;
	return ;
}

static void	exit_char(char **split, t_data *data)
{
	printf("bash: exit: %s: numeric argument required\n", split[1]);
	free_array(split);
	split = NULL;
	data->error->status = 2;
	data->error->exit = TRUE;
	return ;
}

static void	exit_normal(char **split, t_data *data)
{
	free_array(split);
	split = NULL;
	data->error->exit = TRUE;
	return ;
}

void	builtin_exit(t_data *data)
{
	char	**split;

	split = ft_split(data->buffer, ' ');
	if (!split[1])
		exit_normal(split, data);
	else if (ft_ischar(split[1]))
		exit_char(split, data);
	else if (!ft_ischar(split[1]))
	{
		if (!split[2])
		{
			data->error->status = ft_atoi(split[1]);
			exit_normal(split, data);
		}
		else
			no_exit(split, data);
	}
}
