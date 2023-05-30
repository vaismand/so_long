/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:15 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/30 15:22:17 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_argv(int argc, char **argv, t_game *game)
{
	int	map_argv_len;

	game->map_alloc = false;
	if (argc > 2)
		ft_error_msg("C`mon, it's too much arguments!", game);
	if (argc < 2)
		ft_error_msg("Probably you should add map file?", game);
	map_argv_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_argv_len - 4], ".ber", 4))
		ft_error_msg("Map file extention is wrong!", game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	ft_check_argv(argc, argv, game);
	ft_init_game(game, argv);
	check_map(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
	mlx_loop_hook(game->mlx_ptr, ft_render_map, game);
	mlx_loop(game->mlx_ptr);
	ft_free_malloc(game);
}
