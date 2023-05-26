/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:15 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/26 22:15:33 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int    main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_game	*game;
		game = malloc(sizeof(t_game));
		ft_init_game(game, argv);
		check_map(game);
		mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
		mlx_loop_hook(game->mlx_ptr, ft_render_map, game);
		mlx_loop(game->mlx_ptr);
	}
}
