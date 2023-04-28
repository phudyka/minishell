/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:44:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/04/28 14:53:24y phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/main.h"

static void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        printf("$ > ");
        fflush(stdout);
    }
    else if (signum == SIGQUIT)
    {
        // do nothing
    }
    else if (signum == SIGTSTP)
    {
        // do nothing
    }
}
void ft_signals()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);

	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	signal(SIGTSTP, &signal_handler);
}

