/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:15:39 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/04 12:24:58 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_victory(t_game *game)
{
	ft_printf("You won!\n");
	ft_free_malloc(game);
	exit(0);
}

int	ft_close_game(t_game *game)
{
	ft_printf("You lost!\n");
	ft_free_malloc(game);
	exit(0);
}

void	ft_error_msg(char *msg, t_game *game)
{
	ft_free_malloc(game);
	ft_printf("Error\n%s\n", msg);
	exit(0);
}

void	ft_print_movements(t_game *game, int x, int y)
{
	if (game->map.full[game->player.y + y][game->player.x + x] != '1')
	{
		game->movements++;
		printf("Movements: %d\n", game->movements);
	}
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
