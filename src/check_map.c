/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:28 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/03 20:44:15 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map(t_game *game)
{
	check_rows(game);
	check_columns(game);
	count_map_param(game);
	verify_map_param(game);
}

void	check_rows(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows - 1)
	{
		if (game->map.columns + 1 != ft_strlen(game->map.full[i]))
			ft_error_msg("Map is not rectangular", game);
		if (game->map.full[i][0] != '1' ||
			game->map.full[i][game->map.columns - 1] != '1')
			ft_error_msg("Map is not closed1", game);
		i++;
	}
	if (game->map.columns != ft_strlen(game->map.full[i]))
			ft_error_msg("Map is not rectangular", game);
	if (game->map.full[i][0] != '1' ||
			game->map.full[i][game->map.columns - 1] != '1')
			ft_error_msg("Map is not closed2", game);

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
			if (!ft_strchr("01CEP", game->map.full[i][j]))
				ft_error_msg("Map has invalid characters", game);
			if (game->map.full[i][j] == 'C')
				game->map.coins++;
			if (game->map.full[i][j] == 'E')
			{
				game->map.exit.x = j;
				game->map.exit.y = i;
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
	if (game->player.x == 0 && game->player.y == 0)
		ft_error_msg("Map has no player", game);
}
