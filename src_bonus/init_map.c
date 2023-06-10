/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:13:33 by dvaisman          #+#    #+#             */
/*   Updated: 2023/06/09 17:26:23 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_count_rows(t_game *game)
{
	char	*line;
	int		rows;

	game->fd = open(game->map.file, O_RDONLY);
	if (game->fd < 0)
		ft_error_msg("Error opening map", game);
	rows = 0;
	while (1)
	{
		line = get_next_line(game->fd);
		if (line == 0)
			break ;
		else
		{
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
			free(line);
		}
	}
	close(game->fd);
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
		ft_render_player(game, j, i, game->player_img);
	else if (game->map.full[i][j] == 'X')
		ft_enemy_move(game, j, i);
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
