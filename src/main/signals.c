/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:44:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/25 15:17:17 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

void    sigint(int sig) // Simule un retour a la ligne si un signal SIGINT est recut
{
    (void)sig;
    write(1, "\n", 1);
}

void    sigquit(int sig) // Quand un signal QUIT est recu, permet d'exit en affichant "exit"
{
    (void)sig;
    ft_putstr_fd("exit :", 1);
    ft_putnbr_fd(sig, 1);
    write(1, "\n", 1);
}

void    ft_sigint(int sig) // reinitialise la ligne sans \n
{
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)sig;
}

int ft_ctrlc(int sig) // gere le cas du CTRL + C en appliquant une nouvelle ligne
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)sig;
}

void    ft_signals(void) //configuration de la gestion des signaux
{
    signal(SIGINT, ft_ctrlc);
    signal(SIGQUIT, SIG_IGN);
}