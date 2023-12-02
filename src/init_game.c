/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaismand <vaismand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:54 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/28 22:11:18 by vaismand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		ft_error_msg("MLX init error\n", game);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->map.columns * PXL, game->map.rows * PXL, "so_long");
	if (!game->win_ptr)
		ft_error_msg("MLX window init error\n", game);
}

void	ft_check_argv(int argc, char **argv, t_game *game)
{
	int	map_argv_len;

	game->img_count = 0;
	game->map_alloc = false;
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->visited = NULL;
	game->map.full = NULL;
	game->img = 0;
	game->map.file = argv[1];
	if (argc > 2)
		ft_error_msg("C`mon, it's too much arguments!\n", game);
	if (argc < 2)
		ft_error_msg("Probably you should add map file?\n", game);
	map_argv_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_argv_len - 4], ".ber", 4))
		ft_error_msg("Map file extention is wrong!\n", game);
	if (open(argv[1], O_RDONLY) < 0)
		ft_error_msg("Map file doesn't exist!\n", game);
	game->fd = open(game->map.file, O_RDONLY);
	if (game->fd < 0)
		ft_error_msg("Error opening map\n", game);
}

static int	ft_count_rows(t_game *game)
{
	t_gnl	gnl;
	char	*line;
	int		rows;

	rows = 0;
	game->fd = open(game->map.file, O_RDONLY);
	if (game->fd < 0)
		ft_error_msg("Error opening map\n", game);
	while (1)
	{
		line = get_next_line(gnl, game->fd, game);
		if (line == 0)
			break ;
		else
			rows++;
		game->map.columns = ft_strlen(line);
		free(line);
	}
	if (close(game->fd) < 0)
		ft_error_msg("Error closing map\n", game);
	return (rows);
}

int	ft_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_Q || keysym == KEY_ESC)
		ft_close_game(game);
	else if (keysym == KEY_A || keysym == KEY_LEFT)
	{
		ft_print_movements(game, -1, 0);
		ft_player_move(game, -1, 0, 1);
	}
	else if (keysym == KEY_D || keysym == KEY_RIGHT)
	{
		ft_print_movements(game, 1, 0);
		ft_player_move(game, 1, 0, 0);
	}
	else if (keysym == KEY_W || keysym == KEY_UP)
	{
		ft_print_movements(game, 0, -1);
		ft_player_move(game, 0, -1, game->player_img);
	}
	else if (keysym == KEY_S || keysym == KEY_DOWN)
	{
		ft_print_movements(game, 0, 1);
		ft_player_move(game, 0, 1, game->player_img);
	}
	return (0);
}

void	ft_init_vars(t_game *game)
{
	game->map.columns = 0;
	game->map.rows = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->map.chests = 0;
	game->movements = 0;
	game->player_img = 0;
	game->map.exit_count = 0;
	game->map.player_count = 0;
	game->map.rows = ft_count_rows(game);
	game->visited = malloc(sizeof(bool *) * game->map.rows);
	if (!game->visited)
		ft_error_msg("Malloc error\n", game);
	game->fd = open(game->map.file, O_RDONLY);
	if (game->fd < 0)
		ft_error_msg("Error opening map\n", game);
	game->map_valid = false;
	game->map_alloc = false;
	game->visited_alloc = false;
}
