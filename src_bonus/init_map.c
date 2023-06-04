/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:33 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/04 13:28:12 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_count_rows(char **argv, t_game *game)
{
	char	*line;
	int		fd;
	int		rows;

	fd = open(argv[1], O_RDONLY);
	rows = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		else
		{
			ft_check_empty_line(line, game);
			rows++;
			free(line);
		}
	}
	close(fd);
	return (rows);
}

void	ft_init_map(t_game *game, char **argv)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	fd = open(argv[1], O_RDONLY);
	i = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		else
		{
			game->map.columns = ft_strlen(line);
			game->map.full[++i] = malloc(sizeof(char) * game->map.columns);
			j = -1;
			while (++j < game->map.columns)
				game->map.full[i][j] = line[j];
			game->map.rows++;
			free(line);
		}
	}
	free(line);
	close(fd);
}

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

void	ft_render_options(t_game *game, int i, int j)
{
	if (game->map.full[i][j] == '1')
		ft_render_img(game, game->img[0], j, i);
	else if (game->map.full[i][j] == 'C')
		ft_chest_anim(game, j, i);
	else if (game->map.full[i][j] == 'E' && game->map.coins == 0)
		ft_render_img(game, game->img[8], j, i);
	else if (game->map.full[i][j] == 'E')
		ft_render_img(game, game->img[9], j, i);
	else if (game->map.full[i][j] == 'P')
		ft_render_img(game, game->img[2], j, i);
	else if (game->map.full[i][j] == 'X')
		ft_render_img(game, game->img[10], j, i);
	else
		ft_render_img(game, game->img[1], j, i);
}

int	ft_render_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.rows)
	{
		j = -1;
		while (++j < game->map.columns)
		{
			ft_render_options(game, i, j);
		}
	}
	ft_print_movements(game);
	ft_player_move(game, 0, 0, game->player_img);
	return (0);
}
