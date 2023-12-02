/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaismand <vaismand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:28 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/28 22:13:19 by vaismand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_check_rows(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.rows)
	{
		if (game->map.full[i] == NULL || game->map.full[i][0] == '\0')
			ft_error_msg("Empty or uninitialized row in map\n", game);
		if (game->map.full[i][0] == '\n')
			ft_error_msg("Map row starts with newline\n", game);
		if (game->map.full[i][0] != '1' ||
			game->map.full[i][game->map.columns - 1] != '1')
			ft_error_msg("Map is not closed or not rectangular\n", game);
	}
}

static void	ft_count_map_param(t_game *game)
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
				ft_error_msg("Map has invalid characters\n", game);
			if (game->map.full[i][j] == 'C')
				game->map.chests++;
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

static void	ft_check_columns(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.columns)
	{
		if (game->map.full[0][i] != '1'
			|| game->map.full[game->map.rows - 1][i] != '1')
			ft_error_msg("Map is not closed or not rectangular\n", game);
		i++;
	}
}

void	ft_verify_map_param(t_game *game)
{
	if (game->map.chests == 0)
		ft_error_msg("Map has no chests\n", game);
	if (game->map.exit_count == 0)
		ft_error_msg("Map has no exit\n", game);
	if (game->map.exit_count > 1)
		ft_error_msg("Map has more than one exit\n", game);
	if (game->map.player_count == 0)
		ft_error_msg("Map has no player\n", game);
	if (game->map.player_count != 1)
		ft_error_msg("Map has more than one player\n", game);
}

void	ft_check_map(t_game *game)
{
	if (game->map.rows == game->map.columns)
		ft_error_msg("Map is not rectangular\n", game);
	if (game->map.rows < 3 || game->map.columns < 3)
		ft_error_msg("Map is too small\n", game);
	if (game->map.rows > 100 || game->map.columns > 100)
		ft_error_msg("Map is too big\n", game);
	ft_check_columns(game);
	ft_check_rows(game);
	ft_count_map_param(game);
}
