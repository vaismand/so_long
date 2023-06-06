/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:54 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/06 10:38:55 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	ft_init_vars(t_game *game, char **argv)
{
	game->map.rows = 0;
	game->map.columns = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->map.coins = 0;
	game->movements = 0;
	game->player_img = 0;
	game->img_count = 0;
	game->img = 0;
	game->map.exit_count = 0;
	game->map.file = argv[1];
	game->map.full = malloc(sizeof(char *) * ft_count_rows(game));
	if (!game->map.full)
		ft_error_msg("Malloc error", game);
	game->visited = malloc(sizeof(bool *) * ft_count_rows(game));
	if (!game->visited)
		ft_error_msg("Malloc error", game);
	game->map_valid = false;
}
