/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaismand <vaismand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:59 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/26 11:37:44 by vaismand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_render_player(t_game *game, int x, int y, int player_sprite)
{
	if (game->map.full[y][x] == 'P' && player_sprite == 0)
		ft_render_img(game, game->img[2], x, y);
	else if (game->map.full[y][x] == 'P' && player_sprite == 1)
		ft_render_img(game, game->img[3], x, y);
	else if (game->map.full[y][x] == 'P' && player_sprite == 2)
		ft_render_img(game, game->img[7], x, y);
	else if (game->map.full[y][x] == 'P' && player_sprite == 3)
		ft_render_img(game, game->img[8], x, y);
}

static int	ft_player_exit(t_game *game, int player_sprite, int x, int y)
{
	game->player.next_x = game->player.x + x;
	game->player.next_y = game->player.y + y;
	if (game->player.x == game->map.exit.x \
		&& game->player.y == game->map.exit.y)
	{
		if (game->player.next_x != game->map.exit.x \
			|| game->player.next_y != game->map.exit.y)
		{
			if (player_sprite == 2)
				game->player_img = 0;
			else if (player_sprite == 3)
				game->player_img = 1;
		}
	}
	else if (game->map.full[game->player.next_y][game->player.next_x] == 'E')
	{
		if (player_sprite == 0)
			game->player_img = 2;
		else if (player_sprite == 1)
			game->player_img = 3;
	}
	else
		game->player_img = player_sprite;
	return (game->player_img);
}

void	ft_player_move(t_game *game, int x, int y, int player_sprite)
{
	int	new_x;
	int	new_y;

	game->player_img = player_sprite;
	new_x = game->player.x + x;
	new_y = game->player.y + y;
	if (game->map.full[new_y][new_x] != '1')
	{
		if (game->map.full[new_y][new_x] == 'C')
			game->map.chests--;
		if (game->map.full[new_y][new_x] == 'E' && game->map.chests == 0)
			ft_victory(game);
		game->player_img = ft_player_exit(game, player_sprite, x, y);
		if (game->player.x == game->map.exit.x \
			&& game->player.y == game->map.exit.y)
			game->map.full[game->player.y][game->player.x] = 'E';
		else
			game->map.full[game->player.y][game->player.x] = '0';
		game->player.x = new_x;
		game->player.y = new_y;
		game->map.full[new_y][new_x] = 'P';
		ft_render_player(game, game->player.x, \
			game->player.y, game->player_img);
	}
}

void	ft_init_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	if (game->map.rows == 0 || game->map.columns == 0)
		ft_error_msg("Map is empty\n", game);
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (game->map.full[i][j] == 'P')
			{
				game->player.x = j;
				game->player.y = i;
				game->map.player_count++;
			}
			j++;
		}
		i++;
	}
}
