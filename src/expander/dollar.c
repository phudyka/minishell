/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:14:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/09 04:06:05 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

char *ft_strcpy(char *dest, const char *src)
{
    size_t i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *command_status(const char *input)
{
    char *output = (char *)malloc(ft_strlen(input) * 2 + 10); // Added some extra space for the integer
    if (!output)
    {
        perror("malloc");
        return (NULL);
    }
    snprintf(output, ft_strlen(input) * 2 + 10, "%s%d", input, g_shell.status);
    return (output);
}

char *ft_dollar(const char *str, int sqot)
{
    size_t i = 0, j = 0;
    char *output = (char *)malloc(ft_strlen(str) + 1);

    if (!output)
    {
        perror("malloc");
        return (NULL);
    }

    while (str[i])
    {
        if (str[i] == '$' && !sqot && (isalnum(str[i+1]) || str[i+1] == '_'))
        {
            i++;
            char var_name[256] = {0};
            size_t k = 0;
            while (isalnum(str[i]) || str[i] == '_')
                var_name[k++] = str[i++];
            char *env_value = getenv(var_name);
            if (env_value)
            {
                output = realloc(output, j + strlen(env_value) + ft_strlen(str) - i + 1);
                if (!output)
                {
                    perror("realloc");
                    return (NULL);
                }
                strcpy(output + j, env_value);
                j += strlen(env_value);
            }
        }
        else
        {
            output[j++] = str[i++];
        }
    }
    output[j] = '\0';
    return (output);
}

