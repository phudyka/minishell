/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:44:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/06/13 16:18:40 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

static void ft_sigint(int sig)
{
    (void)sig;
    ft_putstr_fd("\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

static void ft_sigterm(int sig)
{
    (void)sig;
    exit(EXIT_SUCCESS);  
}

static void ft_sigquit(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void ft_signals(void)
{
    struct sigaction sa;
    
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = &ft_sigterm;
    if (sigaction(SIGTERM, &sa, NULL) == -1)
        ft_putstr_fd("Error!: [sigaction(SIGTERM)]\n", 2);
    sa.sa_handler = &ft_sigint;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        ft_putstr_fd("Error!: [sigaction(SIGINT)]\n", 2);
    sa.sa_handler = &ft_sigquit;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        ft_putstr_fd("Error!: [sigaction(SIGQUIT)]\n", 2);
}
