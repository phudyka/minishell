/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:24:06 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/11 03:35:22 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	ft_dquote(int *i, int *j, char *parsed, const char *value)
{
	char	*env_var;

	while (value[(*i)])
	{
		if (value[(*i)] == '$')
		{
			(*i)++;
			env_var = ft_dollar(value + (*i), 1);
			if (env_var)
			{
				ft_strcpy(parsed + *j, env_var);
				*j += ft_strlen(env_var);
				free(env_var);
			}
			while (value[(*i)] && value[(*i)] != '"')
				parsed[(*j)++] = value[(*i)++];
		}
		else
			parsed[(*j)++] = value[(*i)++];
	}
}

static void	ft_squote(int *i, int *j, char *parsed, const char *value)
{
	while (value[(*i)])
		parsed[(*j)++] = value[(*i)++];
}

static void	ft_sequence(int len, char *parsed, const char *value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len && value[i])
	{
		if (value[i] == '"')
			ft_dquote(&i, &j, parsed, value + i);
		else if (value[i] == '\'')
			ft_squote(&i, &j, parsed, value + i);
		else
			parsed[j++] = value[i++];
	}
	parsed[j] = '\0';
}

void	parse_quotes(t_token *tokens)
{
	int		len;
	char	*parsed;

	len = ft_strlen(tokens->value);
	parsed = (char *)malloc(sizeof(char) * (len + 1));
	if (!parsed)
	{
		ft_putstr_fd("Error! [malloc]\n", 2);
		g_shell.status = 12;
		return ;
	}
	ft_sequence(len, parsed, tokens->value);
	free(tokens->value);
	tokens->value = parsed;
}
