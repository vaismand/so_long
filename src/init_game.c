/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:54 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/06 00:49:57 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	game->map.full = malloc(sizeof(char *) * ft_count_rows(argv, game));
	if (!game->map.full)
		ft_error_msg("Malloc error", game);
	game->visited = malloc(sizeof(bool *) * ft_count_rows(argv, game));
	if (!game->visited)
		ft_error_msg("Malloc error", game);
	game->map_valid = false;
}
