/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:14:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/08 19:58:09 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

char *ft_strcpy(char *dest, const char *src)
{
    size_t i;

    i = -1;
    while (src[++i])
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

char *command_status(const char *input)
{
    char *output;
    
    output = (char *)malloc(ft_strlen(input) * 2);
    if (!output)
    {
        perror("malloc");
        return (NULL);
    }
    printf("%s%d", input, g_shell.status);
    return (output);
}

char *ft_dollar(const char *str, int sqot)
{
    size_t i;
    size_t j;
    char *output;
    char *env_value;

    i = 0;
    j = 0;
    output = (char *)malloc(ft_strlen(str) + 1);
    if (!output)
    {
        perror("malloc");
        return (NULL);
    }
    while (str[i])
    {
        if (str[i] == '$' && !sqot)
        {
            i++;
            char var_name[256];
            size_t k = 0;
            while (isalnum(str[i]) || str[i] == '_')
                var_name[k++] = str[i++];
            var_name[k] = '\0';
            env_value = getenv(var_name);
            if (env_value)
            {
                size_t env_len = strlen(env_value);
                if (j + env_len >= ft_strlen(str) + 1)
                {
                    perror("Output buffer overflow");
                    free(output);
                    return (NULL);
                }
                strcpy(output + j, env_value);
                j += env_len;
            }
        }
        else
            output[j++] = str[i++];
    }
    output[j] = '\0';
    return (output);
}
