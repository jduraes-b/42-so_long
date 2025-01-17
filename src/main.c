/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:18:41 by jduraes-          #+#    #+#             */
/*   Updated: 2024/02/04 20:10:12 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data	*initialize(void)
{
	t_data		*gamestate;
	t_position	*player;
	t_position	*exit;
	t_imgs		*img;

	gamestate = (t_data *)ft_calloc(1, sizeof(t_data));
	player = (t_position *)ft_calloc(1, sizeof(t_position));
	gamestate->player = player;
	img = (t_imgs *)ft_calloc(1, sizeof(t_imgs));
	gamestate->img = img;
	exit = (t_position *)ft_calloc(1, sizeof(t_position));
	gamestate->exit = exit;
	return (gamestate);
}

int	deinitialize(t_data *gamestate)
{
	if (gamestate->mlx)
	{
		mlx_destroy_image(gamestate->mlx, gamestate->img->player);
		mlx_destroy_image(gamestate->mlx, gamestate->img->wall);
		mlx_destroy_image(gamestate->mlx, gamestate->img->col);
		mlx_destroy_image(gamestate->mlx, gamestate->img->exit);
		mlx_destroy_image(gamestate->mlx, gamestate->img->bg);
		mlx_destroy_window(gamestate->mlx, gamestate->mlx_win);
		mlx_destroy_display(gamestate->mlx);
	}
	free(gamestate->mlx);
	freegamestate(gamestate);
	return (0);
}

void	freegamestate(t_data *gamestate)
{
	if (gamestate->map)
		doublefree(gamestate->map);
	free(gamestate->player);
	free(gamestate->exit);
	free(gamestate->img);
	free(gamestate);
}

int	main(int argc, char **argv)
{
	t_data	*gamestate;

	if (wrongargs(argc, argv))
		return (1);
	gamestate = initialize();
	if (!mapread(argv[1], gamestate))
	{
		write(1, "map read error", 14);
		deinitialize(gamestate);
		return (1);
	}
	if (!mapcheck(gamestate))
	{
		write(1, "unacceptable map", 16);
		deinitialize(gamestate);
		return (0);
	}
	mlxstart(gamestate);
}
