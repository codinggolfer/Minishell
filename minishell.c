/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halgordzibari <halgordzibari@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:12:15 by eagbomei          #+#    #+#             */
/*   Updated: 2024/08/12 17:23:52 by halgordziba      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_num = 0;

void	init_data(t_input *data, char **env)
{
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	data->tokens = NULL;
	data->vars = set_env(env);
	data->own_env = NULL;
	data->cwd = getcwd(NULL, 1024);
	data->exit_code = 0;
	data->old = malloc(sizeof(struct termios) * 1);
	//data->new = malloc(sizeof(struct termios) * 1);
	//tcgetattr(STDIN_FILENO, data->old);
	rebuild_envp(data);
}

int	check_closed(t_input *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == '\"' || data->line[i] == '\'')
		{
			i = bunny_ears(data->line, i, data->line[i]);
			if (i == -1)
			{
				free (data->line);
				printf("Error: Unmatched quotation mark detected\n");
				return (0);
			}
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
		if (ft_strlen(line) == 0)
		{
			free (line);
			return (0);
		}
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

	i = 0;
	temp = data->cmds;
	while (temp)
	{
		while (temp->cmd.cmd && temp->cmd.cmd[i] != NULL)
		{
			if (is_redirect(temp->cmd.cmd[i]) == 1
				&& (is_redirect(temp->cmd.cmd[i + 1]) == 1
					|| temp->cmd.cmd[i + 1] == NULL))
			{
				data->exit_code = 2;
				if (is_redirect(temp->cmd.cmd[i + 1]) == 1)
					return (error_msg("babatunde shell", NULL,
						"syntax error near unexpected token", 2));
				return (error_msg("babatunde shell", NULL,
						"command not found", 2));
			}
			++i;
		}
		i = 0;
		temp = temp->next;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_input	input;

	if (ac != 1)
		return (0);
	(void)av;
	init_data(&input, envp);
	tcgetattr(STDOUT_FILENO, input.old);
	input.new = input.old;
	tcsetattr(STDIN_FILENO, TCSANOW, input.new);
	while (1)
	{
		check_signal(0);
		if (handle_line(&input) == 0)
			continue ;
		dollar_sign(&input);
		lexer(&input);
		// for (int i = 0; input.tokens[i]; i++)
		// 	printf("%s\n", input.tokens[i]);
		parser(&input);
		// for (int j = 0; input.cmds->cmd.cmd[j]; j++)
		// 	printf("%s\n", input.cmds->cmd.cmd[j]);
		// input.cmds = input.cmds->next;
		// for (int j = 0; input.cmds->cmd.cmd[j]; j++)
		// 	printf("%s\n", input.cmds->cmd.cmd[j]);
		// for (int j = 0; input.own_env[j]; j++)
		// 	printf("%s\n", input.own_env[j]);
		if (check_redirect_errors(&input) == 0)
			run_cmd(&input);
		cleaner(&input);
	}
	exit (0);
	//exit (reset_exit(&input.atr->def_atr, 0));
}
