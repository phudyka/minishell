/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:44:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/14 11:37:14 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	ft_sigquit(int sig)
{
	if (g_signal > 0)
	{
		kill(g_signal, SIGQUIT);
		ft_putstr_fd("^\\Quit (core dumped)\n", 2);
	}
	else
		signal(sig, SIG_IGN);
}

void	restore_termios(t_data *data)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, data->termios);
	free(data->termios);
	data->termios = NULL;
}

static void	ft_sigint(int sig)
{
	(void)sig;
	if (g_signal > 0)
	{
		kill(g_signal, SIGINT);
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
	if (g_signal > 0)
		kill(g_signal, SIGTERM);
	exit(EXIT_SUCCESS);
}

void	ft_signals(t_data *data)
{
	struct termios	new_termios;

	data->termios = (struct termios *)malloc(sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, data->termios) == -1)
	{
		ft_putstr_fd("Error! [tcgetattr]\n", 2);
		data->error->status = 2;
		exit(EXIT_FAILURE);
	}
	new_termios = *data->termios;
	new_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
	{
		ft_putstr_fd("Error! [tcsetattr]\n", 2);
		data->error->status = 2;
		exit(EXIT_FAILURE);
	}
	if (signal(SIGINT, ft_sigint))
		data->error->status = 130;
	signal(SIGTERM, ft_sigterm);
	if (signal(SIGQUIT, ft_sigquit))
		data->error->status = 131;
}
