/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:14:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 03:59:52 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static char	*ft_qmark(const char *str, size_t *i, char *output, size_t *j)
{
	char	status_str[12];

	if (str[*i + 1] == '?')
	{
		snprintf(status_str, sizeof(status_str), "%d", g_shell.status);
		ft_strcpy(output + *j, status_str);
		*j += ft_strlen(status_str);
		(*i)++; // Just increase by one
		return (output);
	}
	return (NULL);
}

static char	*ft_incr_dol(const char *str, size_t *i, char *output, size_t *j)
{
	char	var_name[256];
	size_t	k;
	char	*env_value;

	ft_bzero(var_name, 256);
	k = 0;
	if (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
	{
		(*i)++;
		while (ft_isalnum(str[*i]) || str[*i] == '_')
			var_name[k++] = str[(*i)++];
		env_value = get_from_env(var_name, g_shell.env);
		if (env_value)
		{
			ft_strcpy(output + *j, env_value);
			*j += ft_strlen(env_value);
			free(env_value);
		}
	}
	else
		output[(*j)++] = str[(*i)++];
	return (output);
}

char	*ft_dollar(const char *str, int sqot)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*output;

	i = 0;
	j = 0;
	size = output_size(str);
	output = (char *)malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && !sqot)
		{
			if (ft_qmark(str, &i, output, &j))
				continue ;
			output = ft_incr_dol(str, &i, output, &j);
		}
		else
			output[j++] = str[i++];
	}
	output[j] = '\0';
	return (output);
}
