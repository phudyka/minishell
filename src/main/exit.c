/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:11:55 by phudyka           #+#    #+#             */
/*   Updated: 2023/07/13 16:42:40 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_freeshell(t_data *data, t_env *env, t_token *tokens)
{
	if (data)
		free_data(data);
	if (env)
		free_list(env);
    if (tokens)
        free_token(tokens);
	env = NULL;
	data = NULL;
    tokens = NULL;
}

void	builtin_exit(t_data *data, t_env *env, t_token tokens)
{
	ft_freeshell(data, env, tokens);
    exit (EXIT_SUCCESS);
}
