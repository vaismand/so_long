/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaismand <vaismand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:15 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/29 15:44:25 by vaismand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_run_mlx_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
	mlx_hook(game->win_ptr, DestroyNotify, \
	ButtonPressMask, ft_close_game, game);
	mlx_loop_hook(game->mlx_ptr, ft_render_map, game);
	mlx_loop(game->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		ft_error_msg("Malloc error\n", game);
	ft_check_argv(argc, argv, game);
	ft_init_vars(game);
	if (ft_check_rectangular(game) == 1)
		ft_error_msg("Map is not rectangular\n", game);
	game->fd = open(game->map.file, O_RDONLY);
	if (game->fd < 0)
		ft_error_msg("Error opening map\n", game);
	if (ft_init_map(game) < 0)
		ft_error_msg("Error reading map\n", game);
	ft_fill_map(game);
	ft_check_map(game);
	ft_init_player(game);
	ft_verify_map_param(game);
	ft_is_valid_path(game);
	ft_init_mlx(game);
	ft_init_images(game);
	ft_run_mlx_hooks(game);
	ft_free_malloc(game);
}
