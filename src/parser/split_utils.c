/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:20:34 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/30 01:36:19 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void process_substring(char **s, char **strs, char **sub, size_t *i)
{
	char *end;
	char *temp_sub;
	char *merged_str;

	end = next_word_end(*s, 0);
	temp_sub = ft_substr(*s, 0, end - *s);
	if (temp_sub)
	{
		merged_str = ft_strjoin(*sub, temp_sub);
		free(temp_sub);
		*sub = merged_str;
		*s = end;
	}
	strs[(*i)++] = *sub;
}


static void	no_quote(t_data *data, char **s, char **strs, size_t *i)
{
	char	*sub;
	char	*expanded;

	sub = get_trimmed_word(*s);
	if (sub[0] == '$')
	{
		expanded = ft_dollar(data, sub, 0);
		if (expanded)
		{
			strs[(*i)++] = expanded;
			free(sub);
		}
	}
	else
		strs[(*i)++] = sub;
	*s = next_word_end(*s, 0);
}

static void	s_quote(char **s, char **strs, size_t *i)
{
	char	*start;
	char	*end;
	char	*sub;

	start = *s + 1;
	end = next_word_end(start, '\'');
	sub = ft_substr(start, 0, end - start);
	*s = end + 1;
	if (sub && **s && **s != ' ' && **s != '\t')
		process_substring(s, strs, &sub, i);
	else
		strs[(*i)++] = sub;
}

static void	d_quote(t_data *data, char **s, char **strs, size_t *i)
{
	char	*start;
	char	*end;
	char	*sub;

	start = *s + 1;
	end = next_word_end(start, '"');
	sub = ft_substr(start, 0, end - start);
	if (ft_strchr(sub, '$'))
	{
		char *expanded = ft_dollar(data, sub, 0);
		free(sub);
		sub = expanded ? expanded : sub;
	}
	*s = end + 1;
	if (sub && **s && **s != ' ' && **s != '\t')
		process_substring(s, strs, &sub, i);
	else
		strs[(*i)++] = sub;
}

static void	process_words(char *s, char **strs, size_t *i, char **temp)
{
	char *merged;

	if (*temp)
	{
		merged = ft_strjoin(*temp, strs[*i - 1]);
		free(strs[*i - 1]);
		strs[*i - 1] = merged;
		*temp = NULL;
	}
	if (*s && *s != ' ' && *s != '\t')
	{
		*temp = strs[*i - 1];
		strs[*i - 1] = NULL;
		(*i)--;
	}
}

void		ft_process(t_data *data, char **strs, size_t *i)
{
	char	*s;
	char	*temp;

	s = data->buffer;
	temp = NULL;
	while (*s)
	{
		s = next_word_start(s);
		if (*s == '\'')
			s_quote(&s, strs, i);
		else if (*s == '"')
			d_quote(data, &s, strs, i);
		else
			no_quote(data, &s, strs, i);
		process_words(s, strs, i, &temp);
	}
}
