/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:15:39 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/24 15:45:07 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*gnl_strjoin(char *left_str, t_gnl gnl, t_game *game)
{
	gnl.str = malloc(sizeof(char) * (ft_strlen(left_str) + \
		ft_strlen(gnl.buff) + 1));
	if (!gnl.str)
	{
		free(left_str);
		free(gnl.buff);
		ft_error_msg("Malloc error\n", game);
	}
	gnl.i = 0;
	while (gnl.i < ft_strlen(left_str))
	{
		gnl.str[gnl.i] = left_str[gnl.i];
		gnl.i++;
	}
	gnl.j = 0;
	while (gnl.j < ft_strlen(gnl.buff))
	{
		gnl.str[gnl.i + gnl.j] = gnl.buff[gnl.j];
		gnl.j++;
	}
	gnl.str[gnl.i + gnl.j] = '\0';
	free(left_str);
	return (gnl.str);
}

int	ft_victory(t_game *game)
{
	ft_printf("You won!\n");
	ft_free_malloc(game);
	exit(0);
}

int	ft_close_game(t_game *game)
{
	ft_printf("You lost!\n");
	ft_free_malloc(game);
	exit(0);
}

void	ft_print_movements(t_game *game, int x, int y)
{
	if (game->map.full[game->player.y + y][game->player.x + x] != '1')
	{
		game->movements++;
		printf("Movements: %d\n", game->movements);
	}
}

bool	ft_is_within_bounds(t_game *game, int row, int col)
{
	return (row >= 0 && row < game->map.rows
		&& col >= 0 && col < game->map.columns);
}
