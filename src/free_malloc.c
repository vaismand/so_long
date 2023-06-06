/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:58:29 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/06 15:24:00 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_malloc(t_game *game)
{
	if (game->map_alloc == true)
	{
		ft_destroy_img(game);
		ft_free_map(game);
		ft_free_visited(game);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free(game);
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

void	ft_free_visited(t_game *game)
{
	int	i;

	i = 0;
	if (game->visited_alloc == true)
	{
		while (i < game->map.rows)
		{
			free(game->visited[i]);
			i++;
		}
	}
	free(game->visited);
}

void	ft_destroy_img(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->img_count && game->img[i].img_ptr != NULL)
	{
		if (game->img[i].img_ptr != NULL)
			mlx_destroy_image(game->mlx_ptr, game->img[i].img_ptr);
		i++;
	}
	free(game->img);
}
