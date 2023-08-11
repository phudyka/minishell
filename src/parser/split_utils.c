/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:25:33 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/11 03:41:00 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static char	**sub_start_to_end(const char *start, const char *end,
		char **strs, size_t *i)
{
	char	*sub;

	if (*start == '\'' || *start == '"')
	{
		start++;
		end--;
	}
	sub = ft_substr(start, 0, end - start);
	if (!sub)
	{
		while (*i > 0)
			free(strs[--(*i)]);
		free(strs);
		return (NULL);
	}
	if (*start == '\'')
		strs[(*i)++] = sub;
	else
	{
		strs[(*i)++] = ft_dollar(sub, false);
		free(sub);
	}
	return (strs);
}

static void	process_without_quote(const char **s, char **strs, size_t *i)
{
	const char	*start;
	const char	*end;

	start = *s;
	*s = next_word_end(*s, 0);
	end = *s;
	if (start < end)
		sub_start_to_end(start, end, strs, i);
}

static void	process_single_quote(const char *start, char **strs, size_t *i)
{
	const char	*end;

	end = next_word_end(start, '\'') - 1;
	strs[(*i)++] = ft_substr(start, 0, end - start);
}

static void	process_double_quote(const char *start, char **strs, size_t *i)
{
	const char	*end;
	char		*intermediate_sub;

	end = next_word_end(start, '"') - 1;
	intermediate_sub = ft_substr(start, 0, end - start);
	if (strchr(intermediate_sub, '$'))
	{
		strs[(*i)++] = ft_dollar(intermediate_sub, 0);
		free(intermediate_sub);
	}
	else
		strs[(*i)++] = intermediate_sub;
}

void	ft_process(const char *s, char **strs, size_t *i)
{
	char	qot;

	while (*s)
	{
		s = next_word_start(s);
		if (*s == '\'' || *s == '"')
		{
			qot = *s++;
			if (qot == '\'')
				process_single_quote(s, strs, i);
			else
				process_double_quote(s, strs, i);
			s = next_word_end(s, qot);
		}
		else
			process_without_quote(&s, strs, i);
	}
}
