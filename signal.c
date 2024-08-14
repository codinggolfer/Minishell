/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:41:58 by eagbomei          #+#    #+#             */
/*   Updated: 2024/06/19 13:36:03 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(int signal)
{
	if (signal == SIGINT)
	{
		g_num = SIGINT;
		write(1, "\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_num = SIGQUIT;
	}
}

static void	heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_num = SIGINT;
		close(0);
		write(1, "> \n", 3);
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	newliner(int signal)
{
	(void) signal;
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		rl_redisplay();
		g_num = SIGINT;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}

}
void	check_signal(int sig)
{
	struct sigaction	sa;	
	
	memset(&sa, 0, sizeof(sa));
	if (sig == 0)
		sa.sa_handler = &newliner;
	if (sig == 1)
		sa.sa_handler = &child;
	else
		sa.sa_handler = &heredoc;
	sa.sa_flags = RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
