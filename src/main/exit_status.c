/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:22:05 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/12 17:10:48 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static int	ft_nbr(char *nbr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (nbr[i] == '-')
	{
		if (!ft_isdigit(nbr[i + 1]))
			return (0);
		i++;
	}
	while (nbr[i])
	{
		if (ft_isdigit(nbr[i]))
			j++;
		i++;
	}
	if (i == j)
		return (1);
	return (0);
}

static void	exit_arg(t_data *data, char **split, int i)
{
	if (split[i + 1] && ft_nbr(split[i + 1]))
	{
		printf("exit\nbash: exit: trop d'arguments\n");
		free_array(split);
		data->error->status = 1;
		data->error->exit = FALSE;
		return ;
	}
	else 
	{
		data->error->status = ft_atoi(split[i]);
		printf("exit\n");
		return ;
	}
}

static void	exit_num(t_data *data, char **split, int i)
{
	printf("exit\nbash: exit: %s: numeric argument required\n", split[i]);
	data->error->status = 2; 
	data->error->exit = TRUE;
	return ;
}

static void	exit_normal(char **split, t_data *data)
{
	free_array(split);
	split = NULL;
	data->error->exit = TRUE;
}

void	builtin_exit(t_data *data)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(data->buffer, ' ');
	if (!split[1])
	{
		exit_normal(split, data);
		return ;
	}
	while (split[++i] && data->error->status == 0)
	{
		if (ft_nbr(split[i]) && (ft_atoi(split[i]) >= INT_MIN
				&& ft_atoi(split[i]) <= INT_MAX))
			exit_arg(data, split, i);
		else
			exit_num(data, split, i);
	}
	free_array(split);
	split = NULL;
	if (data->error->status == 0)
		printf("exit\n");
	data->error->exit = TRUE;
}
