/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:17:32 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/09 15:55:44 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	is_squote(char c)
{
	return (c == '\'');
}

int	is_dquote(char c)
{
	return (c == '\"');
}

static char *ft_sequence(char type, const char *value)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*parsed;

    i = 0;
    j = 1;
    len = ft_strlen(value);
    parsed = (char *)malloc(sizeof(char) * (len - 2));
    if (!parsed)
        return NULL;
    while (j < len - 1)
    {
        if ((type == '\'' && is_squote(value[j])) ||
            (type == '\"' && is_dquote(value[j])))
        {
            j++;
            continue;
        }
        else if (type == '\"' && value[j] == '$')
            parsed[i++] = value[j++];
        else
            parsed[i++] = value[j++];
    }
    parsed[i] = '\0';
    return parsed;
}

void parse_quotes(t_token *tokens)
{
	char	type;
	char	*parsed;
    t_token *temp;
	
	temp = tokens;
    while (temp)
    {
        if (temp->type == QOT && temp->value && temp->value[0])
        {
            type = temp->value[0];
            parsed = ft_sequence(type, temp->value);
            if (!parsed)
                ft_error(QOT, 0);
            free(temp->value);
            temp->value = parsed;
        }
        temp = temp->next;
    }
}
