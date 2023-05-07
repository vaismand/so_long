#include "so_long.h"

void	ft_init_map(t_game *game, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFile not found\n", 2);
		exit(1);
	}
	ft_read_map(game, fd);
	ft_check_map(game);
	ft_init_images(game);
	ft_init_window(game);
	ft_draw_map(game);
	ft_draw_player(game);
	ft_draw_coins(game);
	ft_draw_exit(game);
	ft_draw_movements(game);
	ft_draw_player(game);
	ft_draw_coins(game);
	ft_draw_exit(game);
	ft_draw_movements(game);
	mlx_hook(game->win_ptr, 2, 1L << 0, ft_key_press, game);
	mlx_hook(game->win_ptr, 17, 1L << 17, ft_close, game);
	mlx_loop(game->mlx_ptr);
}

void	ft_read_map(t_game *game, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(fd) > 0)
	{
		if (i == 0)
			game->map.columns = ft_strlen(line);
		if (i == 0)
			game->map.full = malloc(sizeof(char *) * 1);
		else
			game->map.full = ft_realloc_map(game->map.full, i);
		game->map.full[i] = ft_strdup(line);
		i++;
		free(line);
	}
	game->map.rows = i;
}

void	ft_check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (game->map.full[i][j] == MAP_PLAYER)
			{
				game->map.players++;
				game->map.player.x = j;
				game->map.player.y = i;
			}
			if (game->map.full[i][j] == MAP_COLLECTIBLE)
				game->map.coins++;
			if (game->map.full[i][j] == MAP_EXIT)
				game->map.exit++;
			j++;
		}
		i++;
	}
	if (game->map.players != 1 || game->map.coins == 0 || game->map.exit == 0)
	{
		ft_putstr_fd("Error\nWrong map\n", 2);
		exit(1);
	}
}

void	ft_init_images(t_game *game)
{
	game->wall.img = mlx_xpm_file_to_image(game->mlx_ptr, "./res/world//wall_mid.xpm",
			&game->wall.width, &game->wall.height);
	game->floor.img = mlx_xpm_file_to_image(game->mlx_ptr, "./res/world/floor_1.xpm",
			&game->floor.width, &game->floor.height);
	game->coins.img = mlx_xpm_file_to_image(game->mlx_ptr, "./res/world/chest_open.xpm",
			&game->coins.width, &game->coins.height);
	game->open_exit.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./res/world/doors_open.xpm", &game->open_exit.width,
			&game->open_exit.height);
	game->exit_closed.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./res/world/doors_losed.xpm", &game->exit_closed.width,
			&game->exit_closed.height);
	game->player_front.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./img/player_front.xpm", &game->player_front.width,
			&game->player_front.height);
	game->player_left.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./img/player_left.xpm", &game->player_left.width,
			&game->player_left.height);
	game->player_right.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./img/player_right.xpm", &game->player_right.width,
			&game->player_right.height);
	game->player_back.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./img/player_back.xpm", &game->player_back.width,
			&game->player_back.height);
}

void	ft_init_window(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.columns * 64,
			game->map.rows * 64, "so_long");
}
