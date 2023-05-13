#ifndef SO_LONG_H
#define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include "mlx-linux/mlx.h"
# include "mlx-linux/mlx_int.h"
# include "lib/libft/libft.h"

# define IMG_HEIGHT			32
# define IMG_WIDTH			32

# define WALL				'1'
# define FLOOR 				'0'
# define MAP_EXIT 		 	'E'
# define MAP_PLAYER 		'P'
# define MAP_COLLECTIBLE 	'C'
# define MAP_ENEMY 			'X'

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_position
{
	int	x;
	int	y;
}	t_positon;

typedef struct s_map
{
	char		**full;
	int		rows;
	int		columns;
	int		coins;
	int		exit;
	int		players;
	t_positon	player;
}	t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int		movements;
	int		player_sprite;
	t_map		map;
	t_image		wall;
	t_image		floor;
	t_image		coins;
	t_image		open_exit;
	t_image		exit_closed;
	t_image		player_front;
	t_image		player_left;
	t_image		player_right;
	t_image		player_back;
}	t_game;

# endif
