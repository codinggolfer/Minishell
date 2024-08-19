/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:12:15 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/19 21:35:15 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_num = 0;

void	init_data(t_input *data, char **env)
{
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	data->tokens = NULL;
	data->line = NULL;
	data->d_sign = 0;
	data->vars = set_env(env);
	data->own_env = NULL;
	data->cwd = getcwd(NULL, 1024);
	data->exit_code = 0;
	rebuild_envp(data);
	tcgetattr(STDIN_FILENO, &data->old);
	data->new = data->old;
	data->new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &data->new);
}

int	check_closed(t_input *data)
{
	int	i;

	i = 0;
	while (data->line && data->line[i])
	{
		if (data->line[i] == '\"' || data->line[i] == '\'')
		{
			i = bunny_ears(data->line, i, data->line[i]);
			if (i == -1)
			{
				free (data->line);
				printf("Error: Unmatched quotation mark detected\n");
				return (2);
			}
			continue ;
		}
		i++;
	}
	return (1);
}

int	handle_line(t_input *data)
{
	char	*line;

	line = readline("babatunde shell: ");
	if (line)
	{
		add_history(line);
		rl_redisplay();
		data->line = ft_strdup(line);
		free (line);
		return (check_closed(data));
	}
	return (0);
}

int	check_redirect_errors(t_input *data)
{
	int		i;
	t_list	*temp;

	temp = data->cmds;
	while (temp)
	{
		i = 0;
		while (temp->cmd.cmd && temp->cmd.cmd[i] != NULL)
		{
			if (is_redirect(temp->cmd.cmd[i]) == 1
				&& ((is_redirect(temp->cmd.cmd[i + 1]) == 1
					|| temp->cmd.cmd[i + 1] == NULL)))
			{
				data->exit_code = 2;
				if (is_redirect(temp->cmd.cmd[i]) == 1)
					return (error_msg(temp->cmd.cmd[i], NULL,
						"syntax error near unexpected token", 2));
				return (error_msg(temp->cmd.cmd[i], NULL,
						"command not found", 2));
			}
			++i;
		}
		temp = temp->next;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_input	input;
	int		i;

	if (ac != 1)
		return (0);
	(void)av;
	g_num = 0;
	init_data(&input, envp);
	while (1)
	{
		check_signal(0);
		i = handle_line(&input);
		if (i == 0)
			break ;
		else if (i == 2)
			continue ; 
		dollar_sign(&input);
		lexer(&input);
		parser(&input);
		if (check_redirect_errors(&input) == 0)
			run_cmd(&input);
		cleaner(&input);
	}
	exit (0);
}
