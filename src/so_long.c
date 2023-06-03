/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:15 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/03 13:47:56 by dvaisman         ###   ########.fr       */
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
	if (open(argv[1], O_RDONLY) < 0)
		ft_error_msg("Map file doesn't exist!", game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	ft_check_argv(argc, argv, game);
	ft_init_vars(game);
	game->map.full = malloc(sizeof(char *) * ft_count_rows(argv, game));
	ft_init_map(game, argv);
	game->map_alloc = true;
	game->mlx_ptr = mlx_init();
	ft_init_images(game);
	ft_init_player(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			game->map.columns * PXL, game->map.rows * PXL, "so_long");
	check_map(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
	mlx_hook(game->win_ptr, DestroyNotify, \
	ButtonPressMask, ft_close_game, game);
	mlx_loop_hook(game->mlx_ptr, ft_render_map, game);
	mlx_loop(game->mlx_ptr);
	ft_free_malloc(game);
}
