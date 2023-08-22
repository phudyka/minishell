/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:14:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/22 08:17:58 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

size_t	get_var_len(const char *str, size_t i)
{
	size_t	len;

	len = 0;
	while (str[i + len] && (ft_isalnum(str[i + len]) || str[i + len] == '_'))
		len++;
	return (len);
}

static size_t	add_variable_size(t_data *data, const char *str, size_t *i)
{
	size_t	k;
	char	*var_name;
	char	*env_value;
	size_t	size;

	k = get_var_len(str, *i + 1);
	var_name = ft_substr(str, *i + 1, k);
	env_value = get_from_env(var_name, data->env);
	if (env_value)
		size = ft_strlen(env_value);
	else
		size = 0;
	*i += k;
	free(var_name);
	free(env_value);
	return (size);
}

static size_t	calc_output_size(t_data *data, const char *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && (isalnum(str[i + 1]) || str[i + 1] == '_'))
			size += add_variable_size(data, str, &i);
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

char	*handle_dollar(t_data *data, const char *str,
						char *output, size_t indices[2])
{
	char	*var_name;
	size_t	k;
	char	*env_value;

	if (!(ft_isalnum(str[indices[0] + 1]) || str[indices[0] + 1] == '_'))
		return (output[indices[1]++] = str[indices[0]++], output);
	indices[0]++;
	k = get_var_len(str, indices[0]);
	var_name = ft_substr(str, indices[0], k);
	env_value = get_from_env(var_name, data->env);
	if (env_value)
	{
		update_values(output, &indices[1], env_value);
		free(env_value);
	}
	free(var_name);
	indices[0] += k;
	return (output);
}

char	*ft_dollar(t_data *data, const char *str, int sqot)
{
	size_t	output_size;
	char	*output;
	size_t	indices[2];

	indices[0] = 0;
	indices[1] = 0;
	output_size = calc_output_size(data, str);
	output = (char *)malloc(output_size + PATH_MAX);
	if (!output)
		return (NULL);
	while (str[indices[0]])
	{
		if (str[indices[0]] == '$' && !sqot)
		{
			if (handle_mark(data, str, output, indices))
				continue ;
			handle_dollar(data, str, output, indices);
		}
		else
			output[indices[1]++] = str[indices[0]++];
	}
	output[indices[1]] = '\0';
	return (output);
}
