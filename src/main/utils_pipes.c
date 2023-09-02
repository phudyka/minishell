/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 09:15:20 by kali              #+#    #+#             */
/*   Updated: 2023/09/02 15:32:37 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parser.h"

static char	*ft_strcat(char *dest, const char *src)
{
	char	*result;

	result = dest;
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (result);
}

char	*concat_strings(char *s1, char *s2)
{
	char	*new_str;

	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s1);
	ft_strcat(new_str, " ");
	ft_strcat(new_str, s2);
	free(s1);
	return (new_str);
}

void	add_result(char **result, char *temp, int *j)
{
	if (ft_strlen(temp) > 0)
	{
		result[*j] = ft_strdup(temp + 1);
		(*j)++;
	}
	free(temp);
}

void	handle_segment(char **input, char **result, int *i, int *j)
{
	char	*temp;

	temp = ft_strdup("");
	while (input[*i] && ft_strcmp(input[*i], "|") != 0)
	{
		temp = concat_strings(temp, input[*i]);
		(*i)++;
	}
	add_result(result, temp, j);
}

char	**group_by_pipes(char **input)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	result = (char **)malloc(sizeof(char *) * 1024);
	if (!result)
		return (NULL);
	while (input[i])
	{
		handle_segment(input, result, &i, &j);
		if (input[i] && strcmp(input[i], "|") == 0)
			i++;
	}
	result[j] = NULL;
	return (result);
}
