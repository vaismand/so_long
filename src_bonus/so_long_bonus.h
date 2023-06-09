/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:26:52 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/09 11:48:56 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include "../mlx-linux/mlx.h"
# include "../mlx-linux/mlx_int.h"
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

# define PXL			32
# define ANIMATION_DELAY	1300

# define WALL				'1'
# define FLOOR 				'0'
# define MAP_EXIT 		 	'E'
# define MAP_PLAYER 		'P'
# define MAP_COLLECTIBLE 	'C'
# define MAP_ENEMY 			'X'

# define KEY_Q				113
# define KEY_ESC  			65307
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100
# define KEY_UP				65362
# define KEY_LEFT			65361
# define KEY_DOWN			65364
# define KEY_RIGHT			65363
# define MOUSE_CLOSE		33

# define WALL_XPM			"res/world/wall.xpm"
# define FLOOR_XPM			"res/world/floor.xpm"
# define CHESTS_1_XPM		"res/world/chest1.xpm"
# define CHESTS_2_XPM		"res/world/chest2.xpm"
# define CHESTS_3_XPM		"res/world/chest3.xpm"
# define CHESTS_4_XPM		"res/world/chest4.xpm"
# define OPEN_EXIT_XPM		"res/world/doors_open.xpm"
# define EXIT_CLOSED_XPM	"res/world/doors_closed.xpm"
# define PLAYER_RIGHT_XPM	"res/world/Player_right.xpm"
# define PLAYER_LEFT_XPM	"res/world/Player_left.xpm"
# define ENEMY_XPM			"res/world/vampire.xpm"
# define RIGHT				0
# define LEFT				1

typedef struct s_image
{
	void	*img_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_map
{
	int			rows;
	int			columns;
	int			coins;
	int			exit_count;
	int			player_count;
	char		*file;
	char		**full;
	t_position	exit;
}	t_map;

typedef struct s_game
{
	int			movements;
	int			player_img;
	int			img_count;
	int			fd;
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	bool		map_alloc;
	bool		map_valid;
	bool		visited_alloc;
	bool		**visited;
	t_image		*img;
	t_position	player;
}	t_game;

int		ft_fill_map(t_game *game, char **argv);
int		ft_render_map(t_game *game);
int		ft_close_game(t_game *game);
int		ft_victory(t_game *game);
int		ft_handle_input(int keysym, t_game *game);
int		ft_handle_mouse(int keysym, t_game *game);
int		ft_count_rows(t_game *game);
void	ft_init_vars(t_game *game, char **argv);
void	ft_init_game(t_game *game, char **argv);
void	ft_init_map(t_game *game);
void	ft_init_images(t_game *game);
void	ft_init_player(t_game *game);
void	check_map(t_game *game);
void	check_rows(t_game *game);
void	check_columns(t_game *game);
void	verify_map_param(t_game *game);
void	count_map_param(t_game *game);
void	ft_render_player(t_game *game, int x, int y, int player_sprite);
void	ft_render_img(t_game *game, t_image sprite, int column, int line);
void	ft_print_movements(t_game *game);
void	ft_player_move(t_game *game, int x, int y, int player_sprite);
void	ft_error_msg(char *msg, t_game *game);
void	ft_free_malloc(t_game *game);
void	ft_destroy_img(t_game *game);
void	ft_free_map(t_game *game);
void	ft_free_visited(t_game *game);
void	ft_is_valid_path(t_game *game);
bool	ft_check_visited(t_game *game, bool has_path, bool all_visited);
bool	ft_dfs_moves(t_game *game, int x, int y, bool has_path);
bool	ft_visited_map(t_game *game, int player_x, int player_y);
bool	ft_dfs(t_game *game, int x, int y, bool has_path);
bool	ft_is_within_bounds(t_game *game, int row, int col);
t_image	ft_new_image(void *mlx, char *path, t_game *game);

#endif
