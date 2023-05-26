/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:59 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/26 22:14:00 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_render_player(t_game *game, int x, int y)
{
	if (game->map.full[y][x] == 'P')
		ft_render_sprite(game, game->player, x, y);
}

void	ft_player_move(t_game *game, int x, int y)
{
	if (game->map.full[game->player.y + y][game->player.x + x] != '1')
	{
		if (game->map.full[game->player.y + y][game->player.x + x] == 'C')
		{
			game->map.coins--;
		}
		if (game->map.full[game->player.y + y][game->player.x + x] == 'E')
		{
			if (game->map.coins == 0)
				ft_victory(game);
		}
		if (game->player.x == game->map.exit.x && game->player.y == game->map.exit.y)
		{
			game->map.full[game->player.y][game->player.x] = 'E';
			game->player.x += x;
			game->player.y += y;
			game->map.full[game->player.y][game->player.x] = 'P';
		}
		else
		{
			game->map.full[game->player.y][game->player.x] = '0';
			game->player.x += x;
			game->player.y += y;
			game->map.full[game->player.y][game->player.x] = 'P';
		}
		game->movements++;
		ft_render_player(game, game->player.x, game->player.y);
		ft_printf("Movements: %d\n", game->movements);
	}
}

void	ft_init_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (game->map.full[i][j] == 'P')
			{
				game->player.x = j;
				game->player.y = i;
				game->map.full[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
	ft_error_msg("Couldn't find the player. Does it exist?", game);
}