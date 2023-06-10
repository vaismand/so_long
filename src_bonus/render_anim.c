/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:12:37 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/10 13:16:51 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_chest_anim(t_game *game, int x, int y)
{
	static int	animation_timer = 0;

	animation_timer++;
	if (animation_timer <= ANIMATION_DELAY)
		ft_render_img(game, game->img[4], x, y);
	else if (animation_timer >= ANIMATION_DELAY * 4)
	{
		ft_render_img(game, game->img[4], x, y);
		animation_timer = 0;
	}
	else if (animation_timer >= ANIMATION_DELAY * 3
		&& animation_timer < ANIMATION_DELAY * 4)
		ft_render_img(game, game->img[7], x, y);
	else if (animation_timer > ANIMATION_DELAY * 2
		&& animation_timer < ANIMATION_DELAY * 3)
		ft_render_img(game, game->img[6], x, y);
	else if (animation_timer > ANIMATION_DELAY)
		ft_render_img(game, game->img[5], x, y);
}

void	ft_enemy_move(t_game *game, int x, int y)
{
	static int	enemy_timer = 0;

	enemy_timer++;
	if (game->map.full[y + 1][x] != '1' && enemy_timer < ENEMY_DELAY)
	{
		game->map.full[y][x] = '0';
		y++;
		game->map.full[y][x] = 'X';
		ft_render_img(game, game->img[10], x, y);
	}
	else if (game->map.full[y - 1][x] != '1' && enemy_timer > ENEMY_DELAY && enemy_timer < ENEMY_DELAY * 3)
	{
		game->map.full[y][x] = '0';
		y--;
		game->map.full[y][x] = 'X';
		ft_render_img(game, game->img[10], x, y);
	}
	else if (enemy_timer > ENEMY_DELAY * 3)
	{
		enemy_timer = 0;
	}
}
