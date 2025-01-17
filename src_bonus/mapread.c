/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:50:26 by jduraes-          #+#    #+#             */
/*   Updated: 2024/02/04 19:39:01 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	wallcheck(t_data *gamestate)
{
	int	i;

	i = 0;
	while (gamestate->map[0][i] == '1' && gamestate->map[gamestate->ylen
		- 1][i] == '1')
		i++;
	if (gamestate->map[0][i] != '\0' && gamestate->map[gamestate->ylen
		- 1][i] != '\0')
		return (0);
	i = 0;
	while (gamestate->map[i])
	{
		if (gamestate->map[i][0] != '1' || gamestate->map[i][gamestate->xlen
			- 1] != '1')
			return (0);
		i++;
	}
	return (enemycheck(gamestate));
}

int	playercheck(t_data *gamestate)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	j = 0;
	player = 0;
	while (gamestate->map[++i])
	{
		j = -1;
		while (gamestate->map[i][++j])
		{
			if (gamestate->map[i][j] == 'P')
			{
				gamestate->player->x = j;
				gamestate->player->y = i;
				player++;
			}
		}
	}
	if (!player)
		return (0);
	if (!wallcheck(gamestate) || !pathcheck(gamestate))
		return (0);
	return (1);
}

int	mapcheck(t_data *gamestate)
{
	int	i;
	int	j;
	int	exit;

	i = 0;
	j = 0;
	exit = 0;
	while (gamestate->map[i])
	{
		j = 0;
		while (gamestate->map[i][j])
		{
			if (gamestate->map[i][j] == 'C' || manobra(i, j, gamestate))
				gamestate->c++;
			if (gamestate->map[i][j] == 'E')
				exit = tag_exit(i, j, exit, gamestate);
			j++;
		}
		i++;
	}
	if (gamestate->c < 1 || exit != 1)
		return (0);
	if (gamestate->enemycount < 0 || !playercheck(gamestate))
		return (0);
	return (1);
}

int	mapwrite(int fd, t_data *gamestate)
{
	char	*mapstr;
	int		maplen;

	mapstr = malloc(sizeof(char *) * gamestate->ylen * (gamestate->xlen + 1)
			+ 1);
	maplen = read(fd, mapstr, gamestate->ylen * (gamestate->xlen + 1));
	mapstr[maplen] = '\0';
	gamestate->map = ft_split(mapstr, '\n');
	free(mapstr);
	return (1);
}

int	mapread(char *file, t_data *gamestate)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	gamestate->xlen = ft_strlen(line) - 1;
	gamestate->ylen = 0;
	while (line)
	{
		if ((((int)ft_strlen(line) - 1 != gamestate->xlen)
				&& line[ft_strlen(line) - 1] == '\n')
			|| (((int)ft_strlen(line) != gamestate->xlen)
				&& line[ft_strlen(line) - 1] != '\n'))
			return (runitdown(line, fd));
		free(line);
		line = get_next_line(fd);
		gamestate->ylen++;
	}
	free(line);
	return (mapwrite(open(file, O_RDONLY), gamestate));
}
