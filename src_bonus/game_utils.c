/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:15:39 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/24 15:54:14 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

int	ft_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_Q || keysym == KEY_ESC)
		ft_close_game(game);
	else if (keysym == KEY_A || keysym == KEY_LEFT)
	{
		game->movements++;
		ft_player_move(game, -1, 0, 1);
	}
	else if (keysym == KEY_D || keysym == KEY_RIGHT)
	{
		game->movements++;
		ft_player_move(game, 1, 0, 0);
	}
	else if (keysym == KEY_W || keysym == KEY_UP)
	{
		game->movements++;
		ft_player_move(game, 0, -1, game->player_img);
	}
	else if (keysym == KEY_S || keysym == KEY_DOWN)
	{
		game->movements++;
		ft_player_move(game, 0, 1, game->player_img);
	}
	return (0);
}

bool	ft_is_within_bounds(t_game *game, int row, int col)
{
	return (row >= 0 && row < game->map.rows
		&& col >= 0 && col < game->map.columns);
}
