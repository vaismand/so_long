#ifndef SO_LONG_H
#define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <stdbool.h>
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

# define KEY_Q				113
# define KEY_ESC  			65307

# define WALL_XPM			"res/world/wall_mid.xpm"
# define FLOOR_XPM			"res/world/floor_1.xpm"
# define COINS_XPM			"res/world/chest_full.xpm"
# define OPEN_EXIT_XPM		"res/world/doors_open.xpm"
# define EXIT_CLOSED_XPM	"res/world/doors_closed.xpm"

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
	_Bool		map_alloc;
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

void	ft_check_command_line_arguments(int argc, char **argv, t_game *game);
void	ft_init_map(t_game *game, char *argv);
char	*ft_strappend(char **s1, const char *s2);
void	ft_check_for_empty_line(char *map, t_game *game);
void	ft_init_vars(t_game *game);
void	ft_check_map(t_game *game);
void	ft_check_rows(t_game *game);
void	ft_check_columns(t_game *game);
void	ft_read_map(t_game *game, char *argv);
void	ft_count_map_parameters(t_game *game);
void	ft_verify_map_parameters(t_game *game);
void	ft_init_mlx(t_game *game);
void	ft_init_sprites(t_game *game);
t_image	ft_new_image(void *mlx, char *path, t_game *game);
int	ft_render_map(t_game *game);
void	ft_identify_sprite(t_game *game, int x, int y);
void	ft_render_player(t_game *game, int x, int y);
void	ft_render_sprite(t_game *game, t_image sprite, int column, int line);
void	ft_print_movements(t_game *game);
int	ft_handle_input(int keysym, t_game *game);
void	ft_player_move(t_game *game, int x, int y, int player_sprite);
int	ft_victory(t_game *game);
void	ft_error_msg(char *msg, t_game *game);
int	ft_close_game(t_game *game);
void	ft_free_all_allocated_memory(t_game *game);
void	ft_destroy_images(t_game *game);
void	ft_free_map(t_game *game);

# endif
