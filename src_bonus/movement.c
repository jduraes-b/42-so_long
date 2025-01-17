/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:31:18 by jduraes-          #+#    #+#             */
/*   Updated: 2024/02/04 20:15:38 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moveenemy(int y, int x, t_enemy *enemy, t_data *gamestate)
{
	if (gamestate->player->x == x && gamestate->player->y == y)
	{
		ft_printf("L\nOnly took you %d moves", gamestate->moves);
		gg(gamestate);
	}
	else
	{
		gamestate->map[y][x] = 'D';
		gamestate->map[enemy->y][enemy->x] = '0';
		enemy->y = y;
		enemy->x = x;
	}
}

void	moveplayer(int x, int y, t_data *gamestate)
{
	if (gamestate->exit->x == gamestate->player->x
		&& gamestate->exit->y == gamestate->player->y)
	{
		gamestate->map[y][x] = 'P';
		gamestate->map[gamestate->player->y][gamestate->player->x] = 'E';
	}
	else
	{
		gamestate->map[y][x] = 'P';
		gamestate->map[gamestate->player->y][gamestate->player->x] = '0';
	}
	gamestate->player->x = x;
	gamestate->player->y = y;
	ft_printf("Moves: %d\n", ++gamestate->moves);
	maprender(gamestate, -1, -1);
}

void	checkmove(int x, int y, t_data *gamestate)
{
	if (gamestate->map[y][x] == '1')
		return ;
	else if (gamestate->map[y][x] == 'D')
	{
		ft_printf("L\ntry again, you wasted %d moves\n", gamestate->moves);
		gg(gamestate);
	}
	else if (gamestate->map[y][x] == 'E' && gamestate->c == 0)
	{
		ft_printf("W\nonly took you %d moves\n", gamestate->moves);
		gg(gamestate);
	}
	else if (gamestate->map[y][x] == 'C')
	{
		gamestate->c--;
		moveplayer(x, y, gamestate);
	}
	else if (gamestate->map[y][x] == '0' || gamestate->map[y][x] == 'E')
		moveplayer(x, y, gamestate);
}

int	readkey(int key, t_data *gamestate)
{
	if (key == ESC)
	{
		ft_printf("Quitting game.\n");
		gg(gamestate);
	}
	if (key == W)
		checkmove(gamestate->player->x, gamestate->player->y - 1, gamestate);
	else if (key == A)
		checkmove(gamestate->player->x - 1, gamestate->player->y, gamestate);
	else if (key == S)
		checkmove(gamestate->player->x, gamestate->player->y + 1, gamestate);
	else if (key == D)
		checkmove(gamestate->player->x + 1, gamestate->player->y, gamestate);
	return (0);
}
