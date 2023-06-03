/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:49 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/31 19:13:19 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_render_sprite(t_game *game, t_image sprite, int column, int line)
{
	int	x;
	int	y;

	x = column * PXL;
	y = line * PXL;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite.img_ptr, x, y);
}

void	ft_init_images(t_game *game)
{
	void	*mlx;

	mlx = game->mlx_ptr;
	game->wall = ft_new_image(mlx, WALL_XPM, game);
	game->floor = ft_new_image(mlx, FLOOR_XPM, game);
	game->chest_1 = ft_new_image(mlx, CHESTS_1_XPM, game);
	game->chest_2 = ft_new_image(mlx, CHESTS_2_XPM, game);
	game->chest_3 = ft_new_image(mlx, CHESTS_3_XPM, game);
	game->chest_4 = ft_new_image(mlx, CHESTS_4_XPM, game);
	game->o_exit = ft_new_image(mlx, OPEN_EXIT_XPM, game);
	game->c_exit = ft_new_image(mlx, EXIT_CLOSED_XPM, game);
	game->player_r = ft_new_image(mlx, PLAYER_RIGHT_XPM, game);
	game->player_l = ft_new_image(mlx, PLAYER_LEFT_XPM, game);
	game->enemy = ft_new_image(mlx, ENEMY_XPM, game);
}

t_image	ft_new_image(void *mlx, char *path, t_game *game)
{
	t_image	image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path, &image.x, &image.y);
	if (image.img_ptr == NULL)
		ft_error_msg("Couldn't find a image. Does it exist?", game);
	return (image);
}