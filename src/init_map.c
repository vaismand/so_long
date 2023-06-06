/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:33 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/06 10:39:16 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_count_rows(t_game *game)
{
	char	*line;
	int		rows;

	rows = 0;
	game->fd = open(game->map.file, O_RDONLY);
	if (game->fd < 0)
		ft_error_msg("Error opening map", game);
	while (1)
	{
		line = get_next_line(game->fd);
		if (line == 0)
			break ;
		else
		{
			ft_check_empty_line(line, game);
			rows++;
			free(line);
		}
	}
	close(game->fd);
	return (rows);
}

void	ft_init_map(t_game *game)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	game->fd = open(game->map.file, O_RDONLY);
	if (game->fd < 0)
		ft_error_msg("Error opening map", game);
	while (1)
	{
		line = get_next_line(game->fd);
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
	close(game->fd);
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
			if (game->map.full[i][j] == '1')
				ft_render_img(game, game->img[0], j, i);
			else if (game->map.full[i][j] == 'C')
				ft_render_img(game, game->img[6], j, i);
			else if (game->map.full[i][j] == 'E' && game->map.coins == 0)
				ft_render_img(game, game->img[4], j, i);
			else if (game->map.full[i][j] == 'E' && game->map.coins > 0)
				ft_render_img(game, game->img[5], j, i);
			else if (game->map.full[i][j] == 'P')
				ft_render_img(game, game->img[2], j, i);
			else
				ft_render_img(game, game->img[1], j, i);
		}
	}
	ft_player_move(game, 0, 0, game->player_img);
	return (0);
}

void	ft_check_empty_line(char *map, t_game *game)
{
	if (map[0] == '\0' || map[0] == '\n')
		ft_error_msg("Empty line in map", game);
}
