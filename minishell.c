/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagbomei <eagbomei@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:12:15 by eagbomei          #+#    #+#             */
/*   Updated: 2024/05/13 16:57:10 by eagbomei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_input	input;
	char *line;
	input.env = env;

	while (1)
	{
		line = readline("babatunde: ");
		if (!line)
			break ;
		add_history(line);
		int				fd1;
		int				fd2;
		static t_pipe	struk;
	
		if (ac != 5 || *env == NULL)
		{
			ft_putendl_fd("Error input", 1);
			return (0);
		}
		fd1 = open (av[1], O_RDONLY);
		fd2 = open (av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd1 < 0 || fd2 < 0)
		{
			ft_putstr_fd("pipex: ", 1);
			ft_putstr_fd(av[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
			struk.flag = 1;
		}
		struk.env = env;
		struk.path = ft_split(find_path(env), ':');
		pipex(fd1, fd2, av, &struk);
		return (0);
		free(line);
	}
}