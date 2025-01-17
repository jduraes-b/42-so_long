/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:38:28 by jduraes-          #+#    #+#             */
/*   Updated: 2024/03/25 19:32:33 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	moveannouncer(t_data *gamestate)
{
	char	*moves;

	moves = ft_itoa(gamestate->moves);
	mlx_string_put(gamestate->mlx, gamestate->mlx_win, 10,
		(gamestate->ylen * 100) + 18, 0x00FFFFFF, "Moves: ");
	mlx_string_put(gamestate->mlx, gamestate->mlx_win, 60,
		(gamestate->ylen * 100) + 18, 0x00FFFFFF, moves);
	free(moves);
}

void	movepicker(t_data *gamestate, t_enemy *curr)
{
	int	r;

	r = rand() % 4;
	if (r == 0 && (gamestate->map[(curr->y) - 1][curr->x] == '0'
		|| gamestate->map[(curr->y - 1)][curr->x] == 'P'))
		moveenemy((curr->y - 1), curr->x, curr, gamestate);
	else if (r == 1 && (gamestate->map[curr->y][curr->x + 1] == '0'
		|| gamestate->map[curr->y][curr->x + 1] == 'P'))
		moveenemy(curr->y, curr->x + 1, curr, gamestate);
	else if (r == 2 && (gamestate->map[curr->y + 1][curr->x] == '0'
		|| gamestate->map[curr->y + 1][curr->x] == 'P'))
		moveenemy(curr->y + 1, curr->x, curr, gamestate);
	else if (r == 3 && (gamestate->map[curr->y][curr->x - 1] == '0'
		|| gamestate->map[curr->y][curr->x - 1] == 'P'))
		moveenemy(curr->y, curr->x - 1, curr, gamestate);
}

int	enemymove(t_data *gamestate)
{
	t_enemy	*curr;
	int		r;

	if (!gamestate->enemycount)
		return (1);
	curr = gamestate->enemy->root;
	r = rand() % 20;
	while (curr != NULL)
	{
		if (r < 1)
			movepicker(gamestate, curr);
		curr = curr->next;
	}
	return (1);
}

int	enemycheck(t_data *gamestate)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (gamestate->map[++i])
	{
		j = -1;
		while (gamestate->map[i][++j])
		{
			if (gamestate->map[i][j] == 'D')
			{
				gamestate->enemycount++;
				newenemy(i, j, gamestate);
			}
		}
	}
	return (1);
}

void	newenemy(int i, int j, t_data *gamestate)
{
	t_enemy	*enemy;

	enemy = (t_enemy *)ft_calloc(1, sizeof(t_enemy));
	enemy->nr = gamestate->enemycount;
	enemy->x = j;
	enemy->y = i;
	enemy->next = NULL;
	if (gamestate->enemycount == 1)
	{
		gamestate->enemy = enemy;
		gamestate->enemy->root = enemy;
	}
	else
	{
		enemy->root = gamestate->enemy->root;
		gamestate->enemy->next = enemy;
		gamestate->enemy = enemy;
	}
}
