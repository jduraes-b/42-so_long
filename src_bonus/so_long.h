/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:01:38 by jduraes-          #+#    #+#             */
/*   Updated: 2024/01/31 17:51:46 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_position
{
	int			x;
	int			y;
}				t_position;

typedef struct s_imgs
{
	void		*player;
	void		*wall;
	void		*col;
	void		*exit;
	void		*bg;
	void		*enemy;
	void		*enemy1;
	void		*enemy2;
}				t_imgs;

typedef enum e_key
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	ESC = 65307,
}				t_key;

typedef struct s_enemy
{
	struct s_enemy	*root;
	struct s_enemy	*next;
	int				nr;
	int				x;
	int				y;
}	t_enemy;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			xlen;
	int			ylen;
	int			c;
	int			moves;
	int			enemycount;
	t_position	*player;
	t_position	*exit;
	t_imgs		*img;
	t_enemy		*enemy;
}				t_data;

# ifndef BUFFER_SIZE
#  define MAX_LINE_LENGTH 4096
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define ESC 65307

int				wrongargs(int argc, char **argv);
int				mapread(char *file, t_data *gamestate);
int				mapwrite(int fd, t_data *gamestate);
int				mapcheck(t_data *gamestate);
int				playercheck(t_data *gamestate);
int				wallcheck(t_data *gamestate);
int				pathcheck(t_data *gamestate);
int				flood_fill(t_data *gamestate, int x, int y, char **map);
void			mlxstart(t_data *gamestate);
void			setimgs(t_data *gamestate, int size);
void			mlxstart(t_data *gamestate);
void			setimgs(t_data *gamestate, int size);
int				maprender(t_data *gamestate, int i, int j);
void			maprender2(t_data *gamestate, int i, int j);
void			enemyanimation(t_data *gamestate, int i, int j);
int				readkey(int key, t_data *gamestate);
void			checkmove(int x, int y, t_data *gamestate);
void			moveplayer(int x, int y, t_data *gamestate);
void			freegamestate(t_data *gamestate);
int				gg(t_data *gamestate);
t_data			*initialize(void);
int				deinitialize(t_data *gamestate);
int				quitgame(t_data *gamestate);
int				tag_exit(int y, int x, int exit, t_data *gamestate);
int				runitdown(char *line, int fd);
int				enemycheck(t_data *gamestate);
void			newenemy(int i, int j, t_data *gamestate);
void			enemyfree(t_enemy *enemy);
void			moveenemy(int y, int x, t_enemy *enemy, t_data *gamestate);
void			movepicker(t_data *gamestate, t_enemy *curr);
int				enemymove(t_data *gamestate);
void			enemyfree(t_enemy *enemy);
int				manobra(int i, int j, t_data *gamestate);
void			moveannouncer(t_data *gamestate);

#endif
