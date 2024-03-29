/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:39:20 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/24 15:35:17 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	ft_check_visited(t_game *game, bool has_path, bool all_visited)
{
	int	i;
	int	j;

	all_visited = true;
	has_path = true;
	i = -1;
	while (++i < game->map.rows)
	{
		j = -1;
		while (++j < game->map.columns)
		{
			if (game->map.full[i][j] == 'E' && !game->visited[i][j])
			{
				all_visited = false;
				break ;
			}
		}
		if (!all_visited)
			break ;
	}
	if (all_visited)
		game->map_valid = true;
	return (has_path);
}

static bool	ft_dfs(t_game *game, int x, int y, bool has_path)
{
	bool	all_visited;

	game->visited[x][y] = true;
	all_visited = false;
	if (game->map.full[x][y] == 'C' || game->map.full[x][y] == 'E')
	{
		if (game->map.full[x][y] == 'C')
			game->map.chests--;
		if (game->map.full[x][y] == 'E')
			game->map.exit_count--;
		if (game->map.chests == 0 && game->map.exit_count == 0)
			has_path = ft_check_visited(game, has_path, all_visited);
	}
	if (has_path)
		has_path = ft_dfs_moves(game, x, y, has_path);
	return (has_path);
}

static bool	ft_init_visited_map(t_game *game, int player_x, int player_y)
{
	bool	has_path;
	int		i;
	int		j;

	i = 0;
	has_path = true;
	while (i < game->map.rows)
	{
		j = 0;
		game->visited[i] = malloc(sizeof(bool) * game->map.columns);
		game->visited_alloc = true;
		if (!game->visited[i])
			ft_error_msg("Malloc failed\n", game);
		while (j < game->map.columns)
		{
			game->visited[i][j] = false;
			j++;
		}
		i++;
	}
	has_path = ft_dfs(game, player_x, player_y, has_path);
	return (has_path);
}

bool	ft_dfs_moves(t_game *game, int x, int y, bool has_path)
{
	int	new_row;
	int	new_col;
	int	*dx;
	int	*dy;
	int	i;

	dx = (int [4]){0, 0, 1, -1};
	dy = (int [4]){1, -1, 0, 0};
	i = 0;
	while (i < 4 && has_path)
	{
		new_row = x + dx[i];
		new_col = y + dy[i];
		if (ft_is_within_bounds(game, new_row, new_col)
			&& game->map.full[new_row][new_col] != '1'
			&& !game->visited[new_row][new_col])
			has_path = ft_dfs(game, new_row, new_col, has_path);
		i++;
	}
	return (has_path);
}

void	ft_is_valid_path(t_game *game)
{
	bool	path_valid;
	int		chests_tmp;

	chests_tmp = game->map.chests;
	path_valid = ft_init_visited_map(game, game->player.y, game->player.x);
	(void)path_valid;
	if (game->map_valid == false)
		ft_error_msg("There is no valid path for player.\n", game);
	game->map.chests = chests_tmp;
}
