/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:48:36 by jduraes-          #+#    #+#             */
/*   Updated: 2024/02/04 20:25:43 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	manobra(int i, int j, t_data *gamestate)
{
	char	c;

	c = gamestate->map[i][j];
	if (c != '1' && c != '0' && c != 'D' && c != 'E' && c != 'C' && c != 'P')
		gamestate->enemycount = -1;
	return (0);
}

int	gg(t_data *gamestate)
{
	deinitialize(gamestate);
	exit(EXIT_SUCCESS);
	return (0);
}

int	wrongargs(int argc, char **argv)
{
	char	*substr;

	substr = NULL;
	if (argc == 2)
	{
		substr = ft_substr(argv[1], (ft_strlen(argv[1]) - 4), 4);
		if (!ft_strstr(substr, ".ber"))
		{
			free(substr);
			write(1, "wrong arguments", 14);
			return (1);
		}
		free(substr);
		return (0);
	}
	free(substr);
	write(1, "wrong arguments", 14);
	return (1);
}

int	tag_exit(int y, int x, int exit, t_data *gamestate)
{
	gamestate->exit->y = y;
	gamestate->exit->x = x;
	exit++;
	return (exit);
}

int	runitdown(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
