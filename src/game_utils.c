/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:15:39 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/06 14:11:06 by dvaisman         ###   ########.fr       */
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

bool	ft_is_within_bounds(t_game *game, int row, int col)
{
	return (row >= 0 && row < game->map.rows
		&& col >= 0 && col < game->map.columns);
}
