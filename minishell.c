/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:12:15 by eagbomei          #+#    #+#             */
/*   Updated: 2024/07/03 14:17:57 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	init_data(t_input *data, char **env)
{
	data->vars = set_env(env);
	data->own_env = NULL;
	data->cwd = getcwd(NULL, 1024);
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
		if (!line)
		{
			free (line);
			return (0);
		}
		add_history(line);
		if (!strcmp(line, "exit"))
			exit (0);
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
				//return (error_msg(NULL, "babatunde shell",
				//		"syntax error near unexpected token", 2));
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

	init_data(&input, envp);
	while (1)
	{
		signal(SIGINT, newliner); //this is for something like ctrl+c get the newline to the promt
		signal(SIGQUIT, 0); // this should quit the whole program like ctrl+z
		if (handle_line(&input) == 0)
			continue ;
		dollar_sign(&input);
		lexer(&input);
		parser(&input);
		//if (check_redirect_errors(&input) == 0)
			//run_cmd();
	}
	return (0);
}
