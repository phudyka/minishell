/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:44:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/10 20:40:04 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	ft_sigquit(int sig)
{
	(void)sig;
	if (g_shell.pid > 0)
	{
		kill(g_shell.pid, SIGQUIT);
		ft_putstr_fd("^\\Quit (core dumped)\n", 2);
	}
	else
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

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
	struct termios	new_termios;

	g_shell.termios = (struct termios *)malloc(sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, g_shell.termios) == -1)
	{
		ft_putstr_fd("Error! [tcgetattr]\n", 2);
		g_shell.status = 2;
		exit(EXIT_FAILURE);
	}
	new_termios = *g_shell.termios;
	new_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
	{
		ft_putstr_fd("Error! [tcsetattr]\n", 2);
		g_shell.status = 2;
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, ft_sigint);
	signal(SIGTERM, ft_sigterm);
	signal(SIGQUIT, ft_sigquit);
}
