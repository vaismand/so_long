/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:39:20 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/05 23:47:57 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool isWithinBounds(t_game *game, int row, int col) 
{
	return (row >= 0 && row < game->map.rows && col >= 0 && col < game->map.columns);
}

bool dfs(t_game *game, bool visited[game->map.rows][game->map.columns], int x, int y, int chests, int exits, bool hasPath) 
{
    visited[x][y] = true;
	bool allVisited = false;
    int i = 0;
    int j;
    if (game->map.full[x][y] == 'C' || game->map.full[x][y] == 'E')
    {
		if (game->map.full[x][y] == 'C') 
			chests--;
		if (game->map.full[x][y] == 'E')
			exits--;
		printf("Test3\n");
		printf("Chests: %d\n", chests);
		printf("Exits: %d\n", exits);
		if (chests == 0 && exits == 0)
		{
			allVisited = true;
			for (i = 0; i < game->map.rows; i++) 
			{
				for (j = 0; j < game->map.columns; j++) 
				{
					if ((game->map.full[i][j] == 'C' || game->map.full[i][j] == 'E') && !visited[i][j]) 
					{
						allVisited = false;
						break;
					}
					printf("All visited: %d\n", allVisited);
				}
				if (!allVisited) {
					break;
				}
			}
			if (allVisited) {
				game->map_valid = true;
			} else {
				hasPath = false;
			}
		}
    }
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int k = 0;

	while (k < 4 && hasPath) 
	{
        int newRow = x + dx[k];
        int newCol = y + dy[k];
        if (isWithinBounds(game, newRow, newCol) && game->map.full[newRow][newCol] != '1' && !visited[newRow][newCol]) 
		{
			ft_printf("%c\n", game->map.full[newRow][newCol]);
            hasPath = dfs(game, visited, newRow, newCol, chests, exits, hasPath);
        }
        k++;
    }
    return (hasPath);
}

bool isPathValid(t_game *game, int player_x, int player_y) {
	// Define the map
	bool	visited[game->map.rows][game->map.columns];
	bool	hasPath = true;
	int	chests = game->map.coins;
	int	exits = game->map.exit_count;
	int	i = 0;
	int	j;
	// Initialize the visited map
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
	hasPath = dfs(game, visited, player_x, player_y, chests, exits, hasPath);
	printf("test2\n");
	return (hasPath);
}

void	ft_is_valid_path(t_game *game)
{
	bool path_valid;
	
	path_valid = isPathValid(game, game->player.y, game->player.x);
	(void)path_valid;
	if (game->map_valid == false) {
		ft_error_msg("There is no valid path from the player to all collectibles and the exit.", game);
	}
	else {
		ft_putstr_fd("There is a valid path from the player to all collectibles and the exit.\n", 1);
	}
}
