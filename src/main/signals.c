/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:44:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 17:44:48 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	restore_termios(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, g_shell.termios);
	free(g_shell.termios);
	g_shell.termios = NULL;
}

static void	ft_sigint(int sig)
{
	(void)sig;
	if (g_shell.pid > 0)
	{
		kill(g_shell.pid, SIGINT);
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
}

static void	ft_sigterm(int sig)
{
	(void)sig;
	if (g_shell.pid > 0)
		kill(g_shell.pid, SIGTERM);
	restore_termios();
	exit(EXIT_SUCCESS);
}

void	ft_signals(void)
{
	g_shell.termios = (struct termios *)malloc(sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, g_shell.termios) == -1)
	{
		ft_putstr_fd("Error! [tcgetattr]\n", 2);
		g_shell.status = 2;
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, ft_sigint);
	signal(SIGTERM, ft_sigterm);
	signal(SIGQUIT, SIG_IGN);
}
