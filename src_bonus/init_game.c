/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:54 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/04 13:38:43 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_print_movements(t_game *game)
{
	char	*movements;
	char	*line;

	movements = ft_itoa(game->movements);
	line = ft_strjoin("Movements: ", movements);
	free(movements);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 10, 0x00FFFFFF, line);
	free(line);
}

void	check_map(t_game *game)
{
	check_rows(game);
	check_columns(game);
	count_map_param(game);
	verify_map_param(game);
}

void	ft_init_vars(t_game *game)
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
}
