/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:39:20 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/04 21:39:20 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool isWithinBounds(t_game *game, int row, int col) {
	printf("test3\n");
    return (row >= 0 && row < game->map.rows && col >= 0 && col < game->map.columns);
}

bool dfs(t_game *game, bool visited[game->map.rows][game->map.columns], int x, int y, bool hasPath) 
{
    visited[x][y] = true;
    int i = 0;
    int j;
    if (game->map.full[x][y] == 'C' || game->map.full[x][y] == 'E') {
        while (i < game->map.rows) {
            j = 0;
            while (j < game->map.columns) {
                if ((game->map.full[i][j] == 'C' || game->map.full[i][j] == 'E') && !visited[i][j]) {
                    hasPath = false;
                    return hasPath;
                }
                j++;
            }
            i++;
        }
    }
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int k = 0;

    while (k < 4 && hasPath) {
        int newRow = x + dx[k];
        int newCol = y + dy[k];
        if (isWithinBounds(game, newRow, newCol) && game->map.full[newRow][newCol] != '1' && !visited[newRow][newCol]) {
            printf("test4\n");
            hasPath = dfs(game, visited, newRow, newCol, hasPath);
        }
        k++;
    }
    return hasPath;
}

// Function to check if there is a valid path from player to all collectibles and exit
bool isPathValid(t_game *game, int player_x, int player_y) {
	// Define the map
	bool	visited[game->map.rows][game->map.columns];
	bool	hasPath = true;
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
	printf("test1\n");
	hasPath = dfs(game, visited, player_x, player_y, hasPath);
	return (hasPath);
}

void	ft_is_valid_path(t_game *game)
{
	bool path_valid;
	
	path_valid = isPathValid(game, game->player.x, game->player.y);
	if (path_valid == false) {
		ft_error_msg("There is no valid path from the player to all collectibles and the exit.", game);
	}
	else {
		ft_putstr_fd("There is a valid path from the player to all collectibles and the exit.\n", 1);
	}
}
