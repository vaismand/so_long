/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:58:29 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/30 14:47:03 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_malloc(t_game *game)
{
	if (game->map_alloc == true)
	{
		ft_destroy_img(game);
		ft_free_map(game);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		free(game);
	}
}

void	ft_free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		free(game->map.full[i]);
		i++;
	}
	free(game->map.full);
}

void	ft_destroy_img(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->chests.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_l.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_r.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->c_exit.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->o_exit.img_ptr);
}
