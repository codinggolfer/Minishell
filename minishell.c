/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzibari <hzibari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:12:15 by eagbomei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/11 14:00:19 by eagbomei         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2024/06/10 13:49:18 by hzibari          ###   ########.fr       */
=======
/*   Updated: 2024/06/10 14:13:22 by eagbomei         ###   ########.fr       */
>>>>>>> 1f41d7e2ba62cdf974cd0fbb96b47e23b96a7d55
>>>>>>> fdfc809d6990e4c0e163a08a312991e8ffea1202
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_input *data, char **env)
{
	data->vars = set_env(env);
	data->own_env = NULL;
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
		rl_redisplay();
		data->line = ft_strdup(line);
		free (line);
		return (check_closed(data));
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
		lexer(&input);
		// for (int i = 0; input.tokens[i] != '\0'; i++)
		// 	printf("%s\n", input.tokens[i]);
		//parser(&input);
	}

}
