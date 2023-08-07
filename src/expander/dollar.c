/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:14:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/07 18:42:54 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

static void ft_strcpy(char *dest, const char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


void parse_dollar(int *i, int *j, char *new, t_token *curr)
{
   int start;
   int end;
   int len;
   char *cmd;
   char *result;

   start = (*i) + 1;
   end = start;
   len = ft_strlen(curr->value);
   while (end < len && ft_isalnum(curr->value[end]))
       end++;
   if (end > start)
   {
       cmd = ft_strndup(&curr->value[start], end - start);
       result = getenv(cmd);
       if (result)
       {
           ft_strcpy(&new[*j], result);
           (*j) += ft_strlen(result);
       }
       free(cmd);
       (*i) = end - 1;
   }
}
