/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:44:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/05/04 09:32:23 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

static void ft_sigint(int sig)
{
    (void)sig;
    write(1, "\n$ >", 4);
}

static void ft_sigquit(int sig)
{
    (void)sig;
    signal(SIGQUIT, SIG_IGN);
}

static void ft_sigterm(int sig)
{
    (void)sig;
    exit(0);
}

void ft_signals(void)
{
    signal(SIGINT, ft_sigint);
    signal(SIGQUIT, ft_sigquit);
    signal(SIGTERM, ft_sigterm);
}
