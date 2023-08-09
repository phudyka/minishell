/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:53:38 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 22:39:09 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

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

char	*extract_variable(const char *str, size_t *index)
{
	size_t	j;
	char	*var;

	j = 0;
	var = (char *)malloc(sizeof(char) * 256 + 1);
	if (!var)
	{
		perror("Error! : [Malloc Failure]");
		return (NULL);
	}
	while (ft_isalnum(str[*index]) || str[*index] == '_')
		var[j++] = str[(*index)++];
	var[j] = '\0';
	return (var);
}

void	process_variable(const char *str, size_t *i, size_t *size)
{
	char	*env;
	char	*var;

	var = extract_variable(str, i);
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

size_t	output_size(const char *str)
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
			process_variable(str, &i, &size);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
