/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaismand <vaismand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:49 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/25 14:10:37 by vaismand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_image	ft_new_image(void *mlx, char *path, t_game *game)
{
	t_image	image;

	image.img_ptr = mlx_xpm_file_to_image(mlx, path, &image.x, &image.y);
	if (image.img_ptr == NULL)
		ft_error_msg("Failed to load image.\n", game);
	game->img_count++;
	return (image);
}

void	ft_render_img(t_game *game, t_image sprite, int column, int line)
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
	game->img = malloc(sizeof(t_image) * 9);
	if (game->img == NULL)
		ft_error_msg("Failed to allocate memory for images.\n", game);
	game->img[0] = ft_new_image(mlx, WALL_XPM, game);
	game->img[1] = ft_new_image(mlx, FLOOR_XPM, game);
	game->img[2] = ft_new_image(mlx, PLAYER_RIGHT_XPM, game);
	game->img[3] = ft_new_image(mlx, PLAYER_LEFT_XPM, game);
	game->img[4] = ft_new_image(mlx, OPEN_EXIT_XPM, game);
	game->img[5] = ft_new_image(mlx, EXIT_CLOSED_XPM, game);
	game->img[6] = ft_new_image(mlx, CHESTS_XPM, game);
	game->img[7] = ft_new_image(mlx, EXIT_PLAYER_RIGHT_XPM, game);
	game->img[8] = ft_new_image(mlx, EXIT_PLAYER_LEFT_XPM, game);
}
