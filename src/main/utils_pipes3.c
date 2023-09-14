/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 08:14:15 by kali              #+#    #+#             */
/*   Updated: 2023/09/14 08:16:22 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

int	is_redirection_command(char *cmd_part)
{
	return (ft_strnstr(cmd_part, ">", ft_strlen(cmd_part)) != NULL
		|| ft_strnstr(cmd_part, "<", ft_strlen(cmd_part)) != NULL
		|| ft_strnstr(cmd_part, ">>", ft_strlen(cmd_part)) != NULL
		|| ft_strnstr(cmd_part, "<<", ft_strlen(cmd_part)) != NULL);
}

t_pipe	*init_pipe_data(t_data *data, t_env *env, int i)
{
	t_pipe	*pipe_data;

	pipe_data = malloc(sizeof(t_pipe));
	if (!pipe_data)
		return (NULL);
	pipe_data->data = data;
	pipe_data->env = env;
	pipe_data->i = i;
	return (pipe_data);
}
