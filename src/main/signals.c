/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:44:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/08/16 11:39:24 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

static void	ft_sigquit(int sig)
{
	(void)sig;
	if (received_signal > 0)
	{
		kill(received_signal, SIGQUIT);
		ft_putstr_fd("^\\Quit (core dumped)\n", 2);
	}
	else
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
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
	if (received_signal > 0)
	{
		kill(received_signal, SIGINT);
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
	if (received_signal > 0)
		kill(received_signal, SIGTERM);
	exit(EXIT_SUCCESS);
}

void	ft_signals(t_data *data)
{
	struct termios	new_termios;

	data->termios = (struct termios *)malloc(sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, data->termios) == -1)
	{
		ft_putstr_fd("Error! [tcgetattr]\n", 2);
		data->status = 2;
		exit(EXIT_FAILURE);
	}
	new_termios = *data->termios;
	new_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
	{
		ft_putstr_fd("Error! [tcsetattr]\n", 2);
		data->status = 2;
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, ft_sigint);
	signal(SIGTERM, ft_sigterm);
	signal(SIGQUIT, ft_sigquit);
}
