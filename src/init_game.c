/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:54 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/26 22:13:55 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_victory(t_game *game)
{
	ft_printf("You won!\n");
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}


int	ft_close_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}

void	ft_init_vars(t_game *game)
{
	game->map.rows = 0;
	game->map.columns = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->map.coins = 0;
	game->movements = 0;
}

void	ft_init_game(t_game *game, char **argv)
{
	game->mlx_ptr = mlx_init();
	ft_init_vars(game);
	ft_init_images(game);
	ft_size_window(game, argv);
	ft_fill_map(game, argv);
	ft_init_player(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.columns * IMG_HEIGHT, game->map.rows * IMG_WIDTH, "so_long");
}