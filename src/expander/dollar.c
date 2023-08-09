/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:14:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 08:05:47 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

char	*ft_strcpy(char *dest, const char *src)
{
	size_t i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static size_t	calc_output_size(const char *str)
{
	size_t size;
	size_t i;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			char var_name[256] = {0};
			size_t k = 0;
			while (isalnum(str[i]) || str[i] == '_')
				var_name[k++] = str[i++];
			char *env_value = getenv(var_name);
			size += (env_value) ? ft_strlen(env_value) : k;
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}

static char	*handle_question_mark(const char *str, size_t *i, char *output, size_t *j)
{
	char status_str[12];

	if (str[*i + 1] == '?')
	{
		snprintf(status_str, sizeof(status_str), "%d", g_shell.status);
		ft_strcpy(output + *j, status_str);
		*j += ft_strlen(status_str);
		*i += 2;
		return (output);
	}
	return (NULL);
}

static char	*handle_dollar_and_increment(const char *str, size_t *i, char *output, size_t *j)
{
	char	var_name[256];
	size_t	k;
	char	*env_value;

	ft_bzero(var_name, 256);
	k = 0;
	if (isalnum(str[*i + 1]) || str[*i + 1] == '_')
	{
		(*i)++;
		while (isalnum(str[*i]) || str[*i] == '_')
			var_name[k++] = str[(*i)++];
		env_value = get_from_env(var_name, g_shell.env);
		if (env_value)
		{
			ft_strcpy(output + *j, env_value);
			*j += ft_strlen(env_value);
		}
	}
	else
		output[(*j)++] = str[(*i)++];
	return (output);
}

char	*ft_dollar(const char *str, int sqot)
{
	size_t	output_size;
	char	*output;
	size_t	i;
	size_t	j;

	output_size = calc_output_size(str);
	if (!(output = (char *)malloc(output_size + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && !sqot)
		{
			if (handle_question_mark(str, &i, output, &j))
				continue;
			output = handle_dollar_and_increment(str, &i, output, &j);
		}
		else
			output[j++] = str[i++];
	}
	output[j] = '\0';
	return (output);
}
