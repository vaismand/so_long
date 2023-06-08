/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:28 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/08 11:15:02 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_rows(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.rows)
	{
		if (game->map.full[i][0] != '1' ||
			game->map.full[i][game->map.columns - 1] != '1')
			ft_error_msg("Map is not closed or not rectangular", game);
	}
}

void	count_map_param(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (!ft_strchr("01CEPX", game->map.full[i][j]))
				ft_error_msg("Map has invalid characters", game);
			if (game->map.full[i][j] == 'C')
				game->map.coins++;
			if (game->map.full[i][j] == 'E')
			{
				game->map.exit.x = j;
				game->map.exit.y = i;
				game->map.exit_count++;
			}
			j++;
		}
		i++;
	}
}

void	check_columns(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.columns)
	{
		if (game->map.full[0][i] != '1'
			|| game->map.full[game->map.rows - 1][i] != '1')
			ft_error_msg("Map is not closed", game);
		i++;
	}
}

void	verify_map_param(t_game *game)
{
	if (game->map.coins == 0)
		ft_error_msg("Map has no coins", game);
	if (game->map.exit.x == 0 && game->map.exit.y == 0)
		ft_error_msg("Map has no exit", game);
	if (game->map.exit_count > 1)
		ft_error_msg("Map has more than one exit", game);
	if (game->map.player_count != 1)
		ft_error_msg("Map has more than one player", game);
	if (game->map.player_count == 0)
		ft_error_msg("Map has no player", game);
	if (game->map.player_count > 1)
		ft_error_msg("Map has more than one player", game);
}
