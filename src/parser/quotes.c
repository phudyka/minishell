/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:55:50 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 15:53:34 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_dquote(char *parsed, int *j, const char *value)
{
	int		i;
	char	*env_var;

	i = 0;
	while (value[i] != '"' && value[i])
	{
		if (value[i] == '$')
		{
			i++;
			env_var = ft_dollar(value + i, 0);
			if (env_var)
			{
				ft_strcpy(parsed + *j, env_var);
				*j += ft_strlen(env_var);
				free(env_var);
			}
			while (value[i] != '"' && value[i])
				parsed[(*j)++] = value[i++];
		}
		else
			parsed[(*j)++] = value[i++];
	}
}

static void	ft_squote(char *parsed, int *j, const char *value)
{
	int	i;

	i = 0;
	while (value[i] != '\'' && value[i])
		parsed[(*j)++] = value[i++];
}

static void	ft_sequence(int *i, int len, char *parsed, const char *value)
{
	int		j;

	j = 0;
	while (*i < len)
	{
		if (value[*i] == '"')
		{
			(*i)++;
			ft_dquote(parsed, &j, value + *i);
			if (value[*i] == '"')
				(*i)++;
		}
		else if (value[*i] == '\'')
		{
			(*i)++;
			ft_squote(parsed, &j, value + *i);
			if (value[*i] == '\'')
				(*i)++;
		}
		else
			parsed[(j)++] = value[(*i)++];
	}
	parsed[j] = '\0';
}

void	parse_quotes(t_token *tokens)
{
	int		i;
	int		len;
	char	*parsed;

	i = 0;
	len = ft_strlen(tokens->value);
	parsed = (char *)malloc(sizeof(char) * (len + 1));
	if (!parsed)
	{
		ft_putstr_fd("Error ! [malloc]", 2);
		return ;
	}
	ft_sequence(&i, len, parsed, tokens->value);
	free(tokens->value);
	tokens->value = parsed;
}
