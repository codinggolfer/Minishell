/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:41:58 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/19 22:48:38 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_num;

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
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
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
	else if (sig == 1)
		sa.sa_handler = &child;
	else
		sa.sa_handler = &heredoc;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
