/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:58:29 by dvaisman          #+#    #+#             */
/*   Updated: 2023/11/24 17:26:49 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows && game->map.full[i] != NULL)
	{
		if (game->map.full[i])
			free(game->map.full[i]);
		i++;
	}
	free(game->map.full);
}

static void	ft_free_visited(t_game *game)
{
	int	i;

	i = 0;
	if (game->visited_alloc == true)
	{
		while (i < game->map.rows && game->visited[i] != NULL)
		{
			free(game->visited[i]);
			i++;
		}
	}
	free(game->visited);
}

static void	ft_destroy_img(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->img_count && game->img[i].img_ptr != NULL)
	{
		if (game->img[i].img_ptr != NULL)
			mlx_destroy_image(game->mlx_ptr, game->img[i].img_ptr);
		i++;
	}
}

void	ft_error_msg(char *msg, t_game *game)
{
	ft_free_malloc(game);
	ft_putstr_fd(msg, 2);
	exit(0);
}

void	ft_free_malloc(t_game *game)
{
	if (!game)
		exit(0);
	if (game && game->map_alloc == true)
		ft_free_map(game);
	if (game->visited)
		ft_free_visited(game);
	if (game->img_count > 0)
		ft_destroy_img(game);
	if (game->img)
		free(game->img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	if (game)
		free(game);
}
