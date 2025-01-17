/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapread_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:24:41 by jduraes-          #+#    #+#             */
/*   Updated: 2024/02/04 20:24:43 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	flood_fill(t_data *gamestate, int x, int y, char **map)
{
	static int	c;
	static int	exit;

	if (map[x][y] == '1')
		return (0);
	if (map[x][y] == 'C')
		c++;
	else if (map[x][y] == 'E')
		exit++;
	map[x][y] = '1';
	flood_fill(gamestate, x + 1, y, map);
	flood_fill(gamestate, x - 1, y, map);
	flood_fill(gamestate, x, y + 1, map);
	flood_fill(gamestate, x, y - 1, map);
	if (c == gamestate->c && exit == 1)
		return (1);
	return (0);
}

int	pathcheck(t_data *gamestate)
{
	char	**tmap;
	int		i;

	i = -1;
	tmap = calloc(gamestate->ylen + 1, sizeof(char **));
	tmap[gamestate->ylen] = NULL;
	while (++i < gamestate->ylen)
		tmap[i] = ft_strdup(gamestate->map[i]);
	if (!flood_fill(gamestate, gamestate->player->y, gamestate->player->x,
			tmap))
	{
		doublefree(tmap);
		return (0);
	}
	else
		doublefree(tmap);
	return (1);
}
