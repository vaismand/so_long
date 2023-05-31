/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:15:39 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/31 19:13:11 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_print_movements(t_game *game)
{
	char	*movements;

	movements = ft_itoa(game->movements);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 10, 0x00FFFFFF, movements);
	free(movements);
}

int	ft_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_Q || keysym == KEY_ESC)
		ft_close_game(game);
	else if (keysym == KEY_A || keysym == KEY_LEFT)
		ft_player_move(game, -1, 0, 1);
	else if (keysym == KEY_D || keysym == KEY_RIGHT)
		ft_player_move(game, 1, 0, 0);
	else if (keysym == KEY_W || keysym == KEY_UP)
		ft_player_move(game, 0, -1, game->player_img);
	else if (keysym == KEY_S || keysym == KEY_DOWN)
		ft_player_move(game, 0, 1, game->player_img);
	game->movements++;
	ft_printf("Movements: %d\n", game->movements);
	return (0);
}
