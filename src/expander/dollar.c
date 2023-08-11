/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:14:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/11 03:36:14 by kali             ###   ########.fr       */
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

static size_t	add_variable_size(const char *str, size_t *i)
{
	size_t	k;
	char	*var_name;
	char	*env_value;
	size_t	size;

	k = get_var_len(str, *i + 1);
	var_name = ft_substr(str, *i + 1, k);
	env_value = getenv(var_name);
	if (env_value)
		size = ft_strlen(env_value);
	else
		size = 0;
	*i += k;
	free(var_name);
	return (size);
}

static size_t	calc_output_size(const char *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && (isalnum(str[i + 1]) || str[i + 1] == '_'))
			size += add_variable_size(str, &i);
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

char	*handle_dollar(const char *str, size_t *i, char *output, size_t *j)
{
	char	*var_name;
	size_t	k;
	char	*env_value;

	if (!(ft_isalnum(str[*i + 1]) || str[*i + 1] == '_'))
		return (output[(*j)++] = str[(*i)++], output);
	(*i)++;
	k = get_var_len(str, *i);
	var_name = ft_substr(str, *i, k);
	env_value = get_from_env(var_name, g_shell.env);
	if (env_value)
	{
		update_values(output, j, env_value);
		free(env_value);
	}
	free(var_name);
	*i += k;
	return (output);
}

char	*ft_dollar(const char *str, int sqot)
{
	size_t	output_size;
	char	*output;
	size_t	i;
	size_t	j;

	output_size = calc_output_size(str);
	output = (char *)malloc(output_size + PATH_MAX);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && !sqot)
		{
			if (handle_mark(str, &i, output, &j))
				continue ;
			handle_dollar(str, &i, output, &j);
		}
		else
			output[j++] = str[i++];
	}
	output[j] = '\0';
	return (output);
}
