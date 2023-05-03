/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:44:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/03 16:46:59 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

static void sigint_handler(int sig)
{
    (void)sig;
    printf("\n"); 
    fflush(stdout);
}

static void sigquit_handler(int sig)
{
    (void)sig;
}

static void sigterm_handler(int sig)
{
    (void)sig;
    exit(0);
}

void ft_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
    signal(SIGTERM, sigterm_handler);
}
