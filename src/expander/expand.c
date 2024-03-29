/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:53:38 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/31 14:44:36 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	update_values(char *output, size_t *j, char *value)
{
	ft_strcpy(output + *j, value);
	*j += ft_strlen(value);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*extract_variable(t_data *data, const char *str, size_t *index)
{
	size_t	start;
	char	*var;

	start = *index;
	while (ft_isalnum(str[*index]) || str[*index] == '_')
		(*index)++;
	var = ft_substr(str, start, *index - start);
	if (!var)
	{
		ft_putstr_fd("Error! : [Malloc Failure]\n", 2);
		data->error->status = 12;
	}
	return (var);
}

void	process_variable(t_data *data, const char *str, size_t *i, size_t *size)
{
	char	*env;
	char	*var;

	var = extract_variable(data, str, i);
	if (!var)
	{
		*size = 0;
		return ;
	}
	env = getenv(var);
	if (env)
		*size += ft_strlen(env);
	else
		*size += ft_strlen(var);
	free(var);
}

size_t	output_size(t_data *data, const char *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			process_variable(data, str, &i, &size);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
