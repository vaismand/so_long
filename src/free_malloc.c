/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:58:29 by dvaisman          #+#    #+#             */
/*   Updated: 2023/05/27 19:38:52 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_malloc(t_game *game)
{
	if (game->map_alloc == true)
	{
		ft_destroy_img(game);
		ft_printf("test1\n");
		ft_free_map(game);
		ft_printf("test2\n");
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		ft_printf("test3\n");
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
	mlx_destroy_image(game->mlx_ptr, game->coins.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit_closed.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->open_exit.img_ptr);
}