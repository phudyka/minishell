/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:18:00 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/08 17:02:56 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

int    ft_equal(const char *s)
{
    int    i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

void free_array(char **tab)
{
    int i;

    i = 0;
    if (!tab)
        return;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

char	*allocatenate(char *cmd, char *path)
{
	int		len;
	char	*exe;

	len = ft_strlen(path) + ft_strlen(cmd);
	exe = (char *)malloc(sizeof(char) * (len + 1));
	if (!exe)
		return (NULL);
	ft_strlcpy(exe, path, ft_strlen(path) + 1);
	ft_strlcat(exe, cmd, len + ft_strlen(cmd) + 1);
	return (exe);
}

void	free_buff(t_data *data)
{
	free(data->buffer);
	free_array(data->cmd);
	data->cmd = NULL;
	data->buffer = NULL;
}

static unsigned int count_words_buff(const char *str)
{
    int i;
    int t;
    char quote_char;

    i = 0;
    t = 0;

    while (*str)
    {
        if ((*str != ' ') && t == 0)
        {
            t = 1;
            if (*str == '"' || *str == '\'')
            {
                quote_char = *str++;
                while (*str && *str != quote_char)
                    str++;
            }
            i++;
        }
        else if (*str == ' ')
            t = 0;

        if (*str)
            str++;
    }
    return (i);
}

char **ft_split_buff(char const *s)
{
    char **strs;
    size_t i;
    size_t len;
    char quote_char;

    if (!s)
        return (NULL);

    i = 0;
    strs = (char **)malloc(sizeof(char *) * (count_words_buff(s) + 1));
    if (!strs)
        return (NULL);

    while (*s)
    {
        while (*s == ' ' || *s == '\t')
            s++;

        if (*s == '"' || *s == '\'')
        {
            quote_char = *s;
            s++;
            len = 0;
            while (s[len] && s[len] != quote_char)
                len++;
            strs[i++] = ft_substr(s, 0, len);
            if (s[len])
                s += len + 1;
        }
        else
        {
            len = 0;
            while (*s && (*s != ' '))
            {
                len++;
                s++;
            }
            strs[i++] = ft_substr(s - len, 0, len);
        }
    }
    strs[i] = NULL;
    return (strs);
}