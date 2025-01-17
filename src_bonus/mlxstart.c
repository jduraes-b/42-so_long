/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxstart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:21:20 by jduraes-          #+#    #+#             */
/*   Updated: 2024/02/04 20:24:29 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	enemyanimation(t_data *gamestate, int i, int j)
{
	static int	c;

	c++;
	if (c < 200 || (c >= 700 && c <= 1100))
	{
		mlx_put_image_to_window(gamestate->mlx, gamestate->mlx_win,
			gamestate->img->enemy, j * 100, i * 100);
	}
	else
	{
		if (c < 700)
			mlx_put_image_to_window(gamestate->mlx, gamestate->mlx_win,
				gamestate->img->enemy1, j * 100, i * 100);
		else if (c > 1100)
			mlx_put_image_to_window(gamestate->mlx, gamestate->mlx_win,
				gamestate->img->enemy2, j * 100, i * 100);
	}
	if (c > 1600)
		c = 0;
}

void	maprender2(t_data *gamestate, int i, int j)
{
	if (gamestate->map[i][j] == 'E')
		mlx_put_image_to_window(gamestate->mlx, gamestate->mlx_win,
			gamestate->img->exit, j * 100, i * 100);
	else if (gamestate->map[i][j] == 'D')
		enemyanimation(gamestate, i, j);
	else
		mlx_put_image_to_window(gamestate->mlx, gamestate->mlx_win,
			gamestate->img->bg, j * 100, i * 100);
}

int	maprender(t_data *gamestate, int i, int j)
{
	i = rand() % 10;
	mlx_clear_window(gamestate->mlx, gamestate->mlx_win);
	if (i == 0)
		enemymove(gamestate);
	i = -1;
	while (++i < gamestate->ylen)
	{
		j = -1;
		while (++j < gamestate->xlen)
		{
			if (gamestate->map[i][j] == '1')
				mlx_put_image_to_window(gamestate->mlx, gamestate->mlx_win,
					gamestate->img->wall, j * 100, i * 100);
			else if (gamestate->map[i][j] == 'C')
				mlx_put_image_to_window(gamestate->mlx, gamestate->mlx_win,
					gamestate->img->col, j * 100, i * 100);
			else
				maprender2(gamestate, i, j);
		}
	}
	mlx_put_image_to_window(gamestate->mlx, gamestate->mlx_win,
		gamestate->img->player, gamestate->player->x * 100, gamestate->player->y
		* 100);
	moveannouncer(gamestate);
	return (0);
}

void	setimgs(t_data *gamestate, int size)
{
	gamestate->img->player = mlx_xpm_file_to_image(gamestate->mlx,
			"assets/imgs/player.xpm", &size, &size);
	gamestate->img->wall = mlx_xpm_file_to_image(gamestate->mlx,
			"assets/imgs/wall.xpm", &size, &size);
	gamestate->img->col = mlx_xpm_file_to_image(gamestate->mlx,
			"assets/imgs/col.xpm", &size, &size);
	gamestate->img->exit = mlx_xpm_file_to_image(gamestate->mlx,
			"assets/imgs/exit.xpm", &size, &size);
	gamestate->img->bg = mlx_xpm_file_to_image(gamestate->mlx,
			"assets/imgs/bg.xpm", &size, &size);
	gamestate->img->enemy = mlx_xpm_file_to_image(gamestate->mlx,
			"assets/imgs/enemy.xpm", &size, &size);
	gamestate->img->enemy1 = mlx_xpm_file_to_image(gamestate->mlx,
			"assets/imgs/enemy1.xpm", &size, &size);
	gamestate->img->enemy2 = mlx_xpm_file_to_image(gamestate->mlx,
			"assets/imgs/enemy2.xpm", &size, &size);
}

void	mlxstart(t_data *gamestate)
{
	int	size;

	size = 100;
	gamestate->mlx = mlx_init();
	gamestate->mlx_win = mlx_new_window(gamestate->mlx, gamestate->xlen * size,
			gamestate->ylen * size + 25, "so_long");
	setimgs(gamestate, size);
	maprender(gamestate, -1, -1);
	mlx_hook(gamestate->mlx_win, 2, 1L << 0, readkey, gamestate);
	mlx_hook(gamestate->mlx_win, 17, 0, gg, gamestate);
	mlx_loop_hook(gamestate->mlx, maprender, gamestate);
	mlx_loop(gamestate->mlx);
}
