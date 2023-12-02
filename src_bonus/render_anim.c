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
	static clock_t	last_time = 0;
	static int		current_frame = 0;

	game->current_time = clock();
	game->elapsed_time = ((double)(game->current_time - last_time)) \
		/ CLOCKS_PER_SEC;
	game->frame_duration = ANIMATION_DELAY / 1000.0;
	if (game->elapsed_time >= game->frame_duration)
	{
		current_frame++;
		last_time = game->current_time;
		if (current_frame >= 4)
			current_frame = 0;
	}
	if (current_frame == 0)
		ft_render_img(game, game->img[4], x, y);
	else if (current_frame == 1)
		ft_render_img(game, game->img[5], x, y);
	else if (current_frame == 2)
		ft_render_img(game, game->img[6], x, y);
	else if (current_frame == 3)
		ft_render_img(game, game->img[7], x, y);
}

void	ft_count_enemies(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (game->map.full[i][j] == 'X')
			{
				game->map.enemy_count++;
			}
			j++;
		}
		i++;
	}
}

void	ft_init_enemies(t_game *game)
{
	int	i;

	game->enemies = malloc(sizeof(t_enemy) * game->map.enemy_count);
	if (!game->enemies)
		ft_error_msg("Malloc error\n", game);
	game->i = 0;
	game->j = 0;
	i = 0;
	while (game->i < game->map.rows)
	{
		game->j = 0;
		while (game->j < game->map.columns)
		{
			if (game->map.full[game->i][game->j] == 'X')
			{
				game->enemies[i].x = game->j;
				game->enemies[i].y = game->i;
				game->enemies[i].dir = 1;
				game->enemies[i].last_time = clock();
				i++;
			}
			game->j++;
		}
		game->i++;
	}
}

void	ft_enemy_move(t_game *game, t_enemy *enemy)
{
	int	next_y;

	game->current_time = clock();
	if (game->current_time < enemy->last_time)
		enemy->last_time = game->current_time;
	game->elapsed_time = ((double)(game->current_time - enemy->last_time)) \
		/ CLOCKS_PER_SEC;
	if (game->elapsed_time >= 1.0)
	{
		next_y = enemy->y + enemy->dir;
		if (next_y >= 0 && next_y < game->map.rows && \
			game->map.full[next_y][enemy->x] != '1' \
			&& game->map.full[next_y][enemy->x] != 'X' \
			&& game->map.full[next_y][enemy->x] != 'E')
		{
			if (game->map.full[enemy->y][enemy->x] == 'X')
				game->map.full[enemy->y][enemy->x] = '0';
			enemy->y = next_y;
			game->map.full[enemy->y][enemy->x] = 'X';
		}
		else
			enemy->dir *= -1;
		enemy->last_time = game->current_time;
	}
}
